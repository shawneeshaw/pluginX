#include "dtkframeobjectincludes.h"

//-------------------------------------------------------------------------
// class dtkImplementationProxyCollection
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
dtkImplementationProxyCollection * dtkImplementationProxyCollection::New() {
    return new dtkImplementationProxyCollection;
}

//-------------------------------------------------------------------------
int dtkImplementationProxyCollection::GetNumberOfItem() {
    return this->MaxId+1;
}

//-------------------------------------------------------------------------
int dtkImplementationProxyCollection::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbImplementationProxy_s[this->Size];
        for (int i = 0; i < this->Size; i++) {
            memset(&this->Array[i].proxy.classId, 0, sizeof(DGUID));
            this->Array[i].proxy.progId[0] = '\0';
            this->Array[i].proxy.func      = NULL;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;
    return 1;
}

//-------------------------------------------------------------------------
int dtkImplementationProxyCollection::InsertNextItem(dtkImplementationProxy& extension) {
    //@@preconditions
    //@@end preconditions

    this->InsertItem(++this->MaxId, extension);
    return this->MaxId;
}

//-------------------------------------------------------------------------
void dtkImplementationProxyCollection::InsertItem(int pos, dtkImplementationProxy& extension) {
    //@@preconditions
    assert(pos >= 0);
    //@@end preconditions

    _fbImplementationProxy_s * pItem = NULL;
    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    pItem = this->Array + pos;
    assert(pItem != NULL);

    int len = strlen(extension.progId);
    assert(len < 64);

    strcpy(pItem->proxy.progId, extension.progId);
    pItem->proxy.classId = extension.classId;
    pItem->proxy.func    = extension.func;
    return;
}

//-------------------------------------------------------------------------
int dtkImplementationProxyCollection::RemoveItem(dtkImplementationProxy& extension) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    int Id = -1;
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].proxy.classId == extension.classId) {
            memset(&this->Array[i].proxy.classId, 0, sizeof(DGUID));
            this->Array[i].proxy.progId[0] = '\0';
            this->Array[i].proxy.func      = NULL;
            Id = i;
            break;
        }
    }
    assert(Id != -1);
    if (Id != this->MaxId) {
        this->Array[Id].proxy.classId = this->Array[this->MaxId].proxy.classId;
        this->Array[Id].proxy.func    = this->Array[this->MaxId].proxy.func;
        strcpy(this->Array[Id].proxy.progId, this->Array[this->MaxId].proxy.progId);
    }
    this->MaxId--;
    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int dtkImplementationProxyCollection::RemoveAllItems(){
    for (int i = 0; i < this->MaxId + 1; i++) {
        this->Array[i].proxy.func      = NULL;
        this->Array[i].proxy.progId[0] = '\0';
        memset(&this->Array[i].proxy.classId, 0, sizeof(DGUID));
    }
    this->MaxId = -1;
    return this->MaxId;
}

//-------------------------------------------------------------------------
dtkImplementationProxyCollection::_fbImplementationProxy_s* dtkImplementationProxyCollection::Resize(int sz) {
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

    dtkImplementationProxyCollection::_fbImplementationProxy_s * newArray = new dtkImplementationProxyCollection::_fbImplementationProxy_s[newSize];
    for (int j = 0; j < newSize; j++) {
        memset(&newArray[j].proxy.classId, 0, sizeof(DGUID));
        newArray[j].proxy.progId[0] = '\0';
        newArray[j].proxy.func = NULL;
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].proxy.classId = this->Array[i].proxy.classId;
        newArray[i].proxy.func    = this->Array[i].proxy.func;
        strcpy(newArray[i].proxy.progId, this->Array[i].proxy.progId);
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;

    return this->Array;
}

//-------------------------------------------------------------------------
int dtkImplementationProxyCollection::GetNextItem(dtkImplementationProxy& extension) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->TraversalPos > this->MaxId) {
        return 0;
    }
    extension.classId = this->Array[this->TraversalPos].proxy.classId;
    extension.func    = this->Array[this->TraversalPos].proxy.func;
    strcpy(extension.progId, this->Array[this->TraversalPos].proxy.progId);
    this->TraversalPos++;
    return 1;
}

//-------------------------------------------------------------------------
dtkImplementationProxyCollection::dtkImplementationProxyCollection() {
    this->Array  =  NULL;
    this->MaxId  = -1;
    this->Size   =  0;
    this->Extend =  5;
    this->TraversalPos = 0;
}

//-------------------------------------------------------------------------
dtkImplementationProxyCollection::~dtkImplementationProxyCollection() {
    if (this->Array != NULL) {
        delete[] this->Array;
        this->Array = NULL;
    }
}
