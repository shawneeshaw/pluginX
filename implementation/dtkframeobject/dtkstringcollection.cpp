#include "dtkframeobjectincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkStringCollection);

//-------------------------------------------------------------------------
// class dtkStringCollection
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
int dtkStringCollection::GetNumberOfItem() {
    return this->MaxId+1;
}

//-------------------------------------------------------------------------
int dtkStringCollection::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].value != NULL) {
                    delete[] this->Array[i].value;
                    this->Array[i].value = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbString_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].value = NULL;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-------------------------------------------------------------------------
int dtkStringCollection::InsertNextItem(const char* key) {
    //@@preconditons
    assert(key != NULL);
    assert(strlen(key) > 0);
    //@@end preconditions

    this->InsertItem(++this->MaxId, key);
    return this->MaxId;
}

//-------------------------------------------------------------------------
void dtkStringCollection::InsertItem(int pos, const char* key) {
    //@@preconditoins
    assert(pos >= 0);
    assert(key != NULL);
    assert(strlen(key) > 0);
    //@@end preconditons

    _fbString_s * strings = NULL;
    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }
    strings = this->Array + pos;
    assert(strings != NULL);
    int slen = (int)strlen(key);
    strings->value = new char[slen+1];
    strcpy(strings->value, key);
    return;
}

//-------------------------------------------------------------------------
int dtkStringCollection::RemoveItem(const char* key) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(this->Array != NULL);
    //@@end preconditions

    int Id = -1;
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (strcmp(this->Array[i].value, key) == 0) {
            delete[] this->Array[i].value;
            this->Array[i].value = NULL;
            Id = i;
            break;
        }
    }
    assert(Id != -1);
    if (Id != this->MaxId) {
        this->Array[Id].value = this->Array[this->MaxId].value;
        this->Array[this->MaxId].value = NULL;
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int dtkStringCollection::RemoveAllItems(){
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].value != NULL) {
            delete[] this->Array[i].value;
            this->Array[i].value = NULL;
        }
    }
    this->MaxId = -1;
    return this->MaxId;
}

//-------------------------------------------------------------------------
dtkStringCollection::_fbString_s* dtkStringCollection::Resize(int sz) {
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

    dtkStringCollection::_fbString_s * newArray = new dtkStringCollection::_fbString_s[newSize];
    for (int j = 0; j < newSize; j++) {
        newArray[j].value = NULL;
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].value = this->Array[i].value;
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-------------------------------------------------------------------------
int dtkStringCollection::GetNextItem(const char*& key) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->TraversalPos > this->MaxId) {
        return 0;
    }
    key = this->Array[this->TraversalPos].value;
    this->TraversalPos++;
    return 1;
}

//-------------------------------------------------------------------------
dtkStringCollection::dtkStringCollection(){
    this->Array  =  NULL;
    this->MaxId  = -1;
    this->Size   =  0;
    this->Extend =  5;
    this->TraversalPos = 0;
}

//-------------------------------------------------------------------------
dtkStringCollection::~dtkStringCollection() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].value != NULL) {
                delete[] this->Array[i].value;
                this->Array[i].value = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
