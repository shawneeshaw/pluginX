#include "dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
// static declaration
//-----------------------------------------------------------------------------
//
dtkObjectFactoryPool * dtkObjectFactory::FactoryPool = NULL;

//-----------------------------------------------------------------------------
// class dtkObjectFactory
//-----------------------------------------------------------------------------
//
const char* dtkObjectFactory::GetClassName() {
    return "dtkObjectFactory";
}

//-----------------------------------------------------------------------------
dtkObject* dtkObjectFactory::CreateObject(const char* classname) {
    for (int i = 0; i < this->OverrideArrayLength; i++) {
        if (this->OverrideArray[i].EnabledFlag && strcmp(this->OverrideClassNames[i], classname) == 0) {
            return (*this->OverrideArray[i].CreateCallback)();
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
dtkObject* dtkObjectFactory::CreateInstance(const char* classname) {
    //@@precondiitons
    assert(classname != NULL);
    assert(classname[0] != '\0');
    //@@end precondiitons

    ///initialize object factory pool.
    if (dtkObjectFactory::FactoryPool == NULL) {
        dtkObjectFactory::Init();
        assert(dtkObjectFactory::FactoryPool != NULL);
    }  

    ///create object from factory.
    int numSize = dtkObjectFactory::FactoryPool->GetPoolSize();
    for (int i = 0; i < numSize; i++) {
        dtkObjectFactory* factory = dtkObjectFactory::FactoryPool->GetItem(i);
        if (factory == NULL) {
            continue;
        }
        dtkObject* newobject = factory->CreateObject(classname);
        if (newobject != NULL) {
            return newobject;
        }
    }
    return NULL;
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::RegisterFactory(dtkObjectFactory* item) {
    //@@preconditions
    assert(item != NULL);
    //@@end preconditions

    dtkObjectFactory::Init();
    dtkObjectFactory::FactoryPool->InsertItem((char*)item->GetClassName(), item);
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::UnRegisterFactory(dtkObjectFactory* item) {
    //@@preconditions
    assert(item != NULL);
    assert(dtkObjectFactory::FactoryPool != NULL);
    //@@end preconditions

    dtkObjectFactory::FactoryPool->RemoveItem((char*)item->GetClassName());
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::UnRegisterAllFactories() {
    //@@preconditions
    assert(dtkObjectFactory::FactoryPool != NULL);
    //@@end precondiitons

    dtkObjectFactory::FactoryPool->RemoveAll();
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::RegisterOverride(const char* classOverride, const char* subclass, const char* description, int enableFlag, CreateFunction createFunction) {
    //@@preconditions
    assert(classOverride != NULL);
    assert(description != NULL);
    assert(subclass != NULL);
    //@@end preconditions

    //adjust array.
    this->GrowOverrideArray();

    int nextIndex = this->OverrideArrayLength;
    this->OverrideArrayLength++;
    char* override = strcpy(new char[strlen(classOverride)+1], classOverride);
    char* desc = strcpy(new char[strlen(description)+1], description);
    char* ocn =  strcpy(new char[strlen(subclass)+1], subclass);
    this->OverrideClassNames[nextIndex]             = override;
    this->OverrideArray[nextIndex].Description      = desc;
    this->OverrideArray[nextIndex].OverrideWithName = ocn;
    this->OverrideArray[nextIndex].EnabledFlag      = enableFlag;
    this->OverrideArray[nextIndex].CreateCallback   = createFunction;
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::Init() {
    if (dtkObjectFactory::FactoryPool != NULL) {
        return;
    }  
    dtkObjectFactory::FactoryPool = dtkObjectFactoryPool::New();
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::DeInit() {
    if (dtkObjectFactory::FactoryPool == NULL) {
        return;
    }  
    dtkObjectFactory::FactoryPool->Release();
    dtkObjectFactory::FactoryPool = NULL;
}

//-----------------------------------------------------------------------------
void dtkObjectFactory::GrowOverrideArray() {
    if (this->OverrideArrayLength+1 > this->SizeOverrideArray) {
        int newLength = this->OverrideArrayLength + 50;
        OverrideInformation* newArray = new OverrideInformation[newLength];
        char** newNameArray = new char*[newLength];

        for (int i =0; i < this->OverrideArrayLength; i++) {
            newNameArray[i] = this->OverrideClassNames[i];
            newArray[i] = this->OverrideArray[i];
        }
        delete [] this->OverrideClassNames;
        this->OverrideClassNames = newNameArray;
        delete [] this->OverrideArray;
        this->OverrideArray = newArray;
    }
}

//-----------------------------------------------------------------------------
dtkObjectFactory::dtkObjectFactory() {
    this->OverrideArray       = 0;
    this->OverrideClassNames  = 0;
    this->SizeOverrideArray   = 0;
    this->OverrideArrayLength = 0;
}

//-----------------------------------------------------------------------------
dtkObjectFactory::~dtkObjectFactory() {
    for(int i = 0; i < this->OverrideArrayLength; i++) {
        delete [] this->OverrideClassNames[i];
        delete [] this->OverrideArray[i].Description;
        delete [] this->OverrideArray[i].OverrideWithName;
    }
    delete [] this->OverrideArray;
    delete [] this->OverrideClassNames;
    this->OverrideArray      = NULL;
    this->OverrideClassNames = NULL;
}
