#include "dtkpluginframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginExtensionCollection);

//-------------------------------------------------------------------------
// class dtkPluginExtensionCollection
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
int dtkPluginExtensionCollection::GetNumberOfItem() {
    return this->MaxId+1;
}

//-------------------------------------------------------------------------
int dtkPluginExtensionCollection::Allocate(int sz, int ext) {
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
        this->Array = new _fbExtension_s[this->Size];
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
int dtkPluginExtensionCollection::InsertNextItem(dtkPluginExtension* extension) {
    //@@preconditons
    assert(extension != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, extension);
    return this->MaxId;
}

//-------------------------------------------------------------------------
void dtkPluginExtensionCollection::InsertItem(int pos, dtkPluginExtension* extension) {
    //@@preconditoins
    assert(pos >= 0);
    assert(extension != NULL);
    //@@end preconditons

    _fbExtension_s * items = NULL;
    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    items = this->Array + pos;
    assert(items != NULL);
    items->item = extension;
}

//-------------------------------------------------------------------------
int dtkPluginExtensionCollection::RemoveItem(dtkPluginExtension* extension) {
    //@@preconditions
    assert(extension != NULL);
    assert(this->Array != NULL);
    //@@end preconditions

    int id = -1;
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].item == extension) {
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
int dtkPluginExtensionCollection::RemoveAllItems(){
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
dtkPluginExtensionCollection::_fbExtension_s* dtkPluginExtensionCollection::Resize(int sz) {
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

    dtkPluginExtensionCollection::_fbExtension_s * newArray = new dtkPluginExtensionCollection::_fbExtension_s[newSize];
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
int dtkPluginExtensionCollection::GetNextItem(dtkPluginExtension*& extension) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->TraversalPos > this->MaxId) {
        return 0;
    }
    extension = this->Array[this->TraversalPos++].item;
    return 1;
}

//-------------------------------------------------------------------------
dtkPluginExtensionCollection::dtkPluginExtensionCollection(){
    this->Array  =  NULL;
    this->MaxId  = -1;
    this->Size   =  0;
    this->Extend =  5;
    this->TraversalPos = 0;
}

//-------------------------------------------------------------------------
dtkPluginExtensionCollection::~dtkPluginExtensionCollection() {
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
