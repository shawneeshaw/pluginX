#include "dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
// class dtkServiceManager
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
dtkServiceManager * dtkServiceManager::New() {
    return new dtkServiceManager;
}

//-----------------------------------------------------------------------------
void dtkServiceManager::InitializeAllServices() {
    //@@preconditions
    assert(collection != NULL);
    //@@end preconditions

    //according to priority.
    int num = this->collection->GetNumberOfItem();
    if (num > 0) {
        int  * index = new int[num];
        int  * priorities = new int[num];
        assert(priorities != NULL);
        for (int i = 0;  i < num; i++) {
            int priority = 0;
            const char* subkey = 0; 
            dtkService* subservice = 0;
            this->collection->GetItem(i, subkey, subservice, priority);
            assert(subservice != NULL);
            index[i] = i;
            priorities[i] = priority;
        }
        dtkSort::QuickSort(priorities, index, num);
        for (int j = 0; j < num; j++) {
            int _idx = index[j];
            assert(_idx >= 0 && _idx < num);
            int priority = 0;
            const char* subkey = 0; 
            dtkService* subservice = 0;
            this->collection->GetItem(_idx, subkey, subservice, priority);
            assert(subservice != NULL);
            subservice->InitializeService();
        }
        delete[] index;
        delete[] priorities;
    }
}

//-----------------------------------------------------------------------------
void dtkServiceManager::UnloadAllServices() {
    //@@preconditions
    assert(this->collection != NULL);
    //@@end preconditions

    //according to priority.
    int num = this->collection->GetNumberOfItem();
    if (num > 0) {
        int  * index = new int[num];
        int  * priorities = new int[num];
        assert(priorities != NULL);
        for (int i = 0;  i < num; i++) {
            int priority = 0;
            const char* subkey = 0; 
            dtkService* subservice = 0;
            this->collection->GetItem(i, subkey, subservice, priority);
            assert(subservice != NULL);
            index[i] = i;
            priorities[i] = priority;
        }
        dtkSort::QuickSort(priorities, index, num);
        for (int j = num-1; j >= 0; j--) {
            int _idx = index[j];
            assert(_idx >= 0 && _idx < num);
            int priority = 0;
            const char* subkey = 0; 
            dtkService* subservice = 0;
            this->collection->GetItem(_idx, subkey, subservice, priority);
            assert(subservice != NULL);
            subservice->UnloadService();
        }
        delete[] index;
        delete[] priorities;
    }
}

//-----------------------------------------------------------------------------
void dtkServiceManager::AddService(const char* key, dtkService* service, int priority) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(service != NULL);
    assert(this->collection != NULL);
    //@@end preconditions

    this->collection->InsertNextItem(key, service, priority);
}

//-----------------------------------------------------------------------------
void dtkServiceManager::RemoveService(dtkService* service) {
    //@@preconditions
    assert(service != NULL);
    assert(this->collection != NULL);
    //@@end preconditions

    this->collection->RemoveItem(service);
}

//-----------------------------------------------------------------------------
void dtkServiceManager::GetService(const char* key, dtkService*& service) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(service == NULL);
    assert(this->collection != NULL);
    //@@end preconditions

    const char* subkey = 0;
    dtkService* subservice = 0;
    for (this->collection->InitTraversal(); this->collection->GetNextItem(subkey, subservice);) {
        if (strcmp(subkey, key) == 0) {
            service = subservice;
            return;
        }
    }
}

//-----------------------------------------------------------------------------
dtkServiceManager::dtkServiceManager() {    
    this->collection = dtkServiceCollection::New();
    this->collection->Allocate(100, 100);
}

//-----------------------------------------------------------------------------
dtkServiceManager::~dtkServiceManager() {
    if (this->collection != NULL) {
        this->collection->Release();
        this->collection = NULL;
    }
}
