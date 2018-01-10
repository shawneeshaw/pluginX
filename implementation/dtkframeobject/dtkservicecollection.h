#ifndef DTKSERVICECOLLECTION_H
#define DTKSERVICECOLLECTION_H

class dtkService;
class dtkServiceCollection: public dtkObject {
public:
    /** create instance */
    static dtkServiceCollection * New();
    
public:
    /** allocate. */
    virtual int  Allocate(int sz, int ext);

    /** get size */
    virtual int  GetNumberOfItem();

    /** add item */
    virtual int  InsertNextItem(const char* key, dtkService* service, int priority = 0);
    
    /** remove item */
    virtual int  RemoveItem(dtkService* service);
    
    /** remove all */
    virtual int  RemoveAllItems();
    
    /** get item */
    virtual int  GetItem(int pos, const char*& key, dtkService*& service, int& priority);

    /** get next item */
    virtual int  GetNextItem(const char*& key, dtkService*& service);

    /** initial traversal */
    virtual void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbService_s {
        char key[64];
        int  priority;
        dtkService* service;
    };
     
    //constructor.
    dtkServiceCollection();

    //destructor
    virtual ~dtkServiceCollection();

    //resize array
    _fbService_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, const char* key, dtkService* service, int priority);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbService_s* Array;
};

#endif //DTKSERVICECOLLECTION_H
