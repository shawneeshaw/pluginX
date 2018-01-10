#ifndef DTKOBJECTFACTORYPOOL_H
#define DTKOBJECTFACTORYPOOL_H

/** @stereotype container */
class dtkObjectFactoryPool : public dtkObject {

public:
    /** create instance */
    static dtkObjectFactoryPool* New();

public:
    /** get class name */
    virtual const char * GetClassName();

    /** insert new item */
    virtual int InsertItem(char* name, dtkObjectFactory* item);

    /** remove item */
    virtual int RemoveItem(char* name);
    
    /** remove all */
    virtual int RemoveAll();

    /** get number item */
    virtual int GetPoolSize() {return MAX_NUM_STACK; }

    /** get item */
    virtual dtkObjectFactory* GetItem(int i) {return this->m_objStackArray[i].FactoryStack; }

protected:
    //enum 
    enum { MAX_NUM_STACK = 10 };

    //inner structure.
    struct fbFactoryStacks {
        dtkObjectFactory* FactoryStack;
        char id[64];
        char used;
    };

    // constructor
    dtkObjectFactoryPool();

    // destructor
    virtual ~dtkObjectFactoryPool();
    
    fbFactoryStacks m_objStackArray[MAX_NUM_STACK];
};

#endif //DTKOBJECTFACTORYPOOL_H
