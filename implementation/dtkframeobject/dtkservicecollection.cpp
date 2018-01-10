#include "dtkframeobjectincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkServiceCollection);

//-------------------------------------------------------------------------
// class dtkServiceCollection
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
int dtkServiceCollection::GetNumberOfItem() {
    return this->MaxId+1;
}

//-------------------------------------------------------------------------
int dtkServiceCollection::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].service != NULL) {
                    this->Array[i].service->Release();
                    this->Array[i].service = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbService_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].service = NULL;
             this->Array[i].key[0] = '\0';
             this->Array[i].priority = -1;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-------------------------------------------------------------------------
int dtkServiceCollection::InsertNextItem(const char* key, dtkService* service, int priority) {
    //@@preconditons
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(service != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, key, service, priority);
    return this->MaxId;
}

//-------------------------------------------------------------------------
void dtkServiceCollection::InsertItem(int pos, const char* key, dtkService* service, int priority) {
    //@@preconditoins
    assert(pos >= 0);
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(service != NULL);
    //@@end preconditons

    _fbService_s * services = NULL;
    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }
    services = this->Array + pos;
    assert(services != NULL);
    services->service = service;
    services->priority = priority;
    strcpy(services->key, key);
    return;
}

//-------------------------------------------------------------------------
int dtkServiceCollection::RemoveItem(dtkService* service) {
    //@@preconditions
    assert(service != NULL);
    assert(this->Array != NULL);
    //@@end preconditions

    int Id = -1;
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].service == service) {
            this->Array[i].service = NULL;
            Id = i;
            break;
        }
    }
    assert(Id != -1);
    if (Id != this->MaxId) {
        this->Array[Id].service = this->Array[this->MaxId].service;
        strcpy(this->Array[Id].key, this->Array[this->MaxId].key);
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int dtkServiceCollection::RemoveAllItems(){
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].service != NULL) {
            this->Array[i].service->Release();
            this->Array[i].service = NULL;
            this->Array[i].key[0] = '\0';
        }
    }
    this->MaxId = -1;
    return this->MaxId;
}

//-------------------------------------------------------------------------
dtkServiceCollection::_fbService_s* dtkServiceCollection::Resize(int sz) {
    //@@preconditions
    assert(sz > 0);
    //@@end preconditions

    int newSize = 0;
    if (sz >= this->Size) {
        newSize = this->Size + sz;
    }
    else {
        assert(0);
        newSize = sz;
    }

    dtkServiceCollection::_fbService_s * newArray = new dtkServiceCollection::_fbService_s[newSize];
    for (int j = 0; j < newSize; j++) {
        newArray[j].service = NULL;
        newArray[j].key[0] ='\0';
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].service = this->Array[i].service;
        strcpy(newArray[i].key, this->Array[i].key);
    }

    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;

    return this->Array;
}

//-------------------------------------------------------------------------
int dtkServiceCollection::GetItem(int pos, const char*& key, dtkService*& service, int& priority) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (pos < 0 && pos > this->MaxId) {
        return 0;
    }
    service = this->Array[pos].service;
    key     = this->Array[pos].key;
    priority= this->Array[pos].priority;
    return 1;
}

//-------------------------------------------------------------------------
int dtkServiceCollection::GetNextItem(const char*& key, dtkService*& codon) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->TraversalPos > this->MaxId) {
        return 0;
    }
    codon = this->Array[this->TraversalPos].service;
    key   = this->Array[this->TraversalPos].key;
    this->TraversalPos++;
    return 1;
}

//-------------------------------------------------------------------------
dtkServiceCollection::dtkServiceCollection(){
    this->Array  =  NULL;
    this->MaxId  = -1;
    this->Size   =  0;
    this->Extend =  5;
    this->TraversalPos = 0;
}

//-------------------------------------------------------------------------
dtkServiceCollection::~dtkServiceCollection() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].service != NULL) {
                this->Array[i].service->Release();
                this->Array[i].service = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
