#include "dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
// class dtkCreator
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
dtkCreator * dtkCreator::New() {
    return new dtkCreator;
}

//-----------------------------------------------------------------------------
int dtkCreator::CreateObject(REFDGUID clsId, void** ppv) {
    //@@preconditions
    assert(this->ImplementionProxyCollection != NULL);
    //@@end preconditions
    
    int numItem = this->ImplementionProxyCollection->GetNumberOfItem();
    if (numItem > 0) {
        dtkImplementationProxy proxy;
        for (this->ImplementionProxyCollection->InitTraversal(); this->ImplementionProxyCollection->GetNextItem(proxy);) {
            if (IsEqualDGUID(clsId, proxy.classId)) {
                *ppv = proxy.func();
                return 0;
            }
        }
    }
    return -1;
}

//-----------------------------------------------------------------------------
int dtkCreator::CreateObject(const char* progId, void** ppv, int overrided) {
    //@@preconditions
    assert(overrided == 0 || overrided == 1);
    assert(progId != NULL);
    assert(strlen(progId) > 0);
    assert(this->ImplementionProxyCollection != NULL);
    //@@end preconditions
    
    //get override class.
    const char* classId = progId;
    if (overrided == 1) {
        const char* overrideClassId = NULL;
        this->QueryClassOverrideInfo(progId, overrideClassId);
        if (overrideClassId != NULL) {
            classId = overrideClassId;
        }
    }
    assert(classId != NULL);
    
    int numItem = this->ImplementionProxyCollection->GetNumberOfItem();
    if (numItem > 0) {
        dtkImplementationProxy proxy;
        for (this->ImplementionProxyCollection->InitTraversal(); this->ImplementionProxyCollection->GetNextItem(proxy);) {
            if (strcmp(classId, proxy.progId) == 0) {
                *ppv = proxy.func();
                return 0;
            }
        }
    }
    return -1;    
}

//-----------------------------------------------------------------------------
int dtkCreator::InsertImplementationProxy(dtkImplementationProxy& proxy) {
    //@@preconditions
    assert(this->ImplementionProxyCollection != NULL);
    //@@end preconditions

    return this->ImplementionProxyCollection->InsertNextItem(proxy);
}

//-----------------------------------------------------------------------------
int dtkCreator::RemoveImplementationProxy(dtkImplementationProxy& proxy) {
    //@@preconditions
    assert(this->ImplementionProxyCollection != NULL);
    //@@end preconditions

    return this->ImplementionProxyCollection->RemoveItem(proxy);
}

//-----------------------------------------------------------------------------
int dtkCreator::InsertClassOverrideInfo(const char* classInfo, const char* classInfoOverride) {
    //@@preconditions
    assert(classInfo != NULL);
    assert(strlen(classInfo) > 0);
    assert(classInfoOverride != NULL);
    assert(strlen(classInfoOverride) > 0);
    assert(this->pClassOverrideInfo != NULL);
    //@@end preconditions

    StringIdRecType stringRec;
    strcpy(stringRec.inkey.id, classInfo);   
    
    if (this->pClassOverrideInfo->StringIdFind(stringRec.inkey, &stringRec) == STRID_STATUS_OK) {
        this->pClassOverrideInfo->StringIdDelete(stringRec.inkey);
    }

    int slen = (int)strlen(classInfoOverride);
    stringRec.stuff = new char[slen+1];
    strcpy(stringRec.stuff, classInfoOverride);
    return this->pClassOverrideInfo->StringIdInsert(stringRec.inkey, &stringRec);
}

//-----------------------------------------------------------------------------
int dtkCreator::RemoveClassOverrideInfo(const char* classInfo) {
    //@@preconditions
    assert(classInfo != NULL);
    assert(strlen(classInfo) > 0);
    assert(this->pClassOverrideInfo != NULL);
    //@@end preconditions

    StringIdRecType stringRec;
    strcpy(stringRec.inkey.id, classInfo);   
    return this->pClassOverrideInfo->StringIdDelete(stringRec.inkey);
}

//-----------------------------------------------------------------------------
int dtkCreator::QueryClassOverrideInfo(const char* classInfo, const char*& classInfoOverride) {
    //@@preconditions
    assert(classInfo != NULL);
    assert(strlen(classInfo) > 0);
    assert(classInfoOverride == NULL);
    assert(this->pClassOverrideInfo != NULL);
    //@@end preconditions

    StringIdRecType stringRec;
    strcpy(stringRec.inkey.id, classInfo);       
    if (this->pClassOverrideInfo->StringIdFind(stringRec.inkey, &stringRec) == STRID_STATUS_OK) {
        classInfoOverride = stringRec.stuff;
        return 1;
    }
    return 0;
}

//-----------------------------------------------------------------------------
dtkCreator::dtkCreator() {    
    this->pClassOverrideInfo = new dtkHashTableStringOneKey();
    this->ImplementionProxyCollection = dtkImplementationProxyCollection::New();
}

//-----------------------------------------------------------------------------
dtkCreator::~dtkCreator() {
    if (this->pClassOverrideInfo != NULL) {
        delete this->pClassOverrideInfo;
        this->pClassOverrideInfo = NULL;
    }
    if (this->ImplementionProxyCollection != NULL) {
        this->ImplementionProxyCollection->Release();
    }
}
