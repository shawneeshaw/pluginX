#include "dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
// class dtkObjectFactoryPool
//-----------------------------------------------------------------------------
//
dtkObjectFactoryPool* dtkObjectFactoryPool::New() {
    return new dtkObjectFactoryPool;
}

//-----------------------------------------------------------------------------
const char* dtkObjectFactoryPool::GetClassName() {
    return "dtkObjectFactoryPool";
}

//-----------------------------------------------------------------------------
int dtkObjectFactoryPool::InsertItem(char* name, dtkObjectFactory* item) {
    //@@preconditions
    assert(item != NULL);
    assert(name != NULL);
    assert(name[0] != '\0');
    //@@end preconditions

    {
        for (int i = 0; i < MAX_NUM_STACK; i++) {
            if (strcmp(this->m_objStackArray[i].id, name) == 0) {
                return 0;
            }
        }
    }

    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (this->m_objStackArray[i].used == 0) {
            this->m_objStackArray[i].FactoryStack = item; 
            this->m_objStackArray[i].used = 1;
            strcpy(this->m_objStackArray[i].id, name);
            return 1;
        }
    }
    assert(0);
    return 0;
}

//-----------------------------------------------------------------------------
int dtkObjectFactoryPool::RemoveItem(char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(name[0] != '\0');
    //@@end preconditions

    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (strcmp(this->m_objStackArray[i].id, name) == 0) {
            this->m_objStackArray[i].FactoryStack->Release();
            this->m_objStackArray[i].FactoryStack = NULL; 
            this->m_objStackArray[i].used = 0;
            this->m_objStackArray[i].id[0] ='\0';
            return 1;
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
int dtkObjectFactoryPool::RemoveAll() {
    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (this->m_objStackArray[i].FactoryStack != NULL) {
            this->m_objStackArray[i].FactoryStack->Release();
            this->m_objStackArray[i].FactoryStack = NULL;
            this->m_objStackArray[i].used = 0;
            this->m_objStackArray[i].id[0] ='\0';
        }
    }
    return 1;
}

//-----------------------------------------------------------------------------
dtkObjectFactoryPool::dtkObjectFactoryPool() {
    for (int i = 0; i < MAX_NUM_STACK; i++) {
        this->m_objStackArray[i].FactoryStack = NULL;
        this->m_objStackArray[i].id[0] = '\0';
        this->m_objStackArray[i].used  = 0;
    }
}

//-----------------------------------------------------------------------------
dtkObjectFactoryPool::~dtkObjectFactoryPool() {
    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (this->m_objStackArray[i].FactoryStack != NULL) {
            this->m_objStackArray[i].FactoryStack->Release();
            this->m_objStackArray[i].FactoryStack = NULL;
        }
    }
}
