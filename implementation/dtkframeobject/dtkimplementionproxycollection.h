#ifndef DTKIMPLEMENTATIONPROXYCOLLECTION_H
#define DTKIMPLEMENTATIONPROXYCOLLECTION_H

class dtkImplementationProxyCollection : public dtkObject {
public:
    /** create instance */
    static dtkImplementationProxyCollection * New();
    
public:
    /** allocate. */
    int  Allocate(int sz, int ext);

    /** get size */
    int  GetNumberOfItem();

    /** add item */
    int  InsertNextItem(dtkImplementationProxy& proxy);
    
    /** remove item */
    int  RemoveItem(dtkImplementationProxy& proxy);
    
    /** remove all */
    int  RemoveAllItems();
    
    /** get next item */
    int  GetNextItem(dtkImplementationProxy& proxy);

    /** initial traversal */
    void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbImplementationProxy_s {
        dtkImplementationProxy proxy;
    };
     
    //constructor.
    dtkImplementationProxyCollection();

    //destructor
    virtual ~dtkImplementationProxyCollection();

    //resize array
    _fbImplementationProxy_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, dtkImplementationProxy& proxy);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbImplementationProxy_s* Array;
};

#endif //DTKIMPLEMENTATIONPROXYCOLLECTION_H
