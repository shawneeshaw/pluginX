#ifndef DTKCOMMANDOBJECTFACTORY_H
#define DTKCOMMANDOBJECTFACTORY_H

/** @stereotype container */
class dtkObjectFactory : public dtkObject {
public:
    /** create instance */
    static dtkObject* CreateInstance(const char* classname);

    /** initialization */
    static void Init();

    /** de-initialization */
    static void DeInit();
    
    /** register factory */
    static void RegisterFactory(dtkObjectFactory* item);
    
    /** unregister factory */
    static void UnRegisterFactory(dtkObjectFactory* item);

    /** unregister all factories */
    static void UnRegisterAllFactories();

public:
    /** get class name */
    virtual const char * GetClassName();

    // create object 
    virtual dtkObject* CreateObject(const char* classname );

protected:
    // constructor
    dtkObjectFactory();

    // destructor
    virtual ~dtkObjectFactory();    

    //protected variables.
    static dtkObjectFactoryPool* FactoryPool;

protected:
    typedef dtkObject* (*CreateFunction)();
    
    //inner structure.
    struct OverrideInformation {
        char* Description;
        char* OverrideWithName;
        int EnabledFlag;
        CreateFunction CreateCallback;
    };

    OverrideInformation* OverrideArray;
    char** OverrideClassNames;
    int SizeOverrideArray;
    int OverrideArrayLength;
    
    // register object creation information with the factory.
    virtual void RegisterOverride(const char* classOverride, const char* overrideClassName, const char* description, int enableFlag, CreateFunction createFunction);

    // adjust override array.
    virtual void GrowOverrideArray();
};

#endif //DTKCOMMANDOBJECTFACTORY_H
