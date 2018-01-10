#include "dtkpluginframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginCodonCollection);

//-------------------------------------------------------------------------
// class dtkPluginCodonCollection
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
int dtkPluginCodonCollection::GetNumberOfItem() {
    return this->MaxId+1;
}

//-------------------------------------------------------------------------
int dtkPluginCodonCollection::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].item != NULL) {
                    this->Array[i].item->Release();
                    this->Array[i].item = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbCodon_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].item = NULL;;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-------------------------------------------------------------------------
int dtkPluginCodonCollection::InsertNextItem(dtkPluginCodon* codon) {
    //@@preconditons
    assert(codon != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, codon);
    return this->MaxId;
}

//-------------------------------------------------------------------------
void dtkPluginCodonCollection::InsertItem(int pos, dtkPluginCodon* codon) {
    //@@preconditoins
    assert(pos >= 0);
    assert(codon != NULL);
    //@@end preconditons

    _fbCodon_s * items = NULL;
    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    items = this->Array + pos;
    assert(items != NULL);
    items->item = codon;
}

//-------------------------------------------------------------------------
int dtkPluginCodonCollection::RemoveItem(dtkPluginCodon* codon) {
    //@@preconditions
    assert(codon != NULL);
    assert(this->Array != NULL);
    //@@end preconditions

    int id = -1;
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].item == codon) {
            this->Array[i].item = NULL;
            id = i;
            break;
        }
    }
    assert(id != -1);
    if (id != this->MaxId) {
        this->Array[id] = this->Array[this->MaxId];
    }
    this->MaxId--;
    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int dtkPluginCodonCollection::RemoveAllItems(){
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].item != NULL) {
            this->Array[i].item->Release();
            this->Array[i].item = NULL;
        }
    }
    this->MaxId = -1;
    return this->MaxId;
}

//-------------------------------------------------------------------------
dtkPluginCodonCollection::_fbCodon_s* dtkPluginCodonCollection::Resize(int sz) {
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

    dtkPluginCodonCollection::_fbCodon_s * newArray = new dtkPluginCodonCollection::_fbCodon_s[newSize];
    for (int j = 0; j < newSize; j++) {
        newArray[j].item = NULL;
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].item = this->Array[i].item;
    }

    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-------------------------------------------------------------------------
int dtkPluginCodonCollection::GetNextItem(dtkPluginCodon*& codon) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->TraversalPos > this->MaxId) {
        return 0;
    }
    codon = this->Array[this->TraversalPos++].item;
    return 1;
}

//-------------------------------------------------------------------------
dtkPluginCodonCollection::dtkPluginCodonCollection(){
    this->Array  =  NULL;
    this->MaxId  = -1;
    this->Size   =  0;
    this->Extend =  5;
    this->TraversalPos = 0;
}

//-------------------------------------------------------------------------
dtkPluginCodonCollection::~dtkPluginCodonCollection() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].item != NULL) {
                this->Array[i].item->Release();
                this->Array[i].item = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
