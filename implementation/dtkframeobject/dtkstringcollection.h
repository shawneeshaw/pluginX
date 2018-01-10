#ifndef DTKSTRINGCOLLECTION_H
#define DTKSTRINGCOLLECTION_H

class dtkStringCollection: public dtkObject {
public:
    /** create instance */
    static dtkStringCollection * New();
    
public:
    /** allocate. */
    virtual int  Allocate(int sz, int ext);

    /** get size */
    virtual int  GetNumberOfItem();

    /** add item */
    virtual int  InsertNextItem(const char* key);
    
    /** remove item */
    virtual int  RemoveItem(const char* key);
    
    /** remove all */
    virtual int  RemoveAllItems();
    
    /** get next item */
    virtual int  GetNextItem(const char*& key);

    /** initial traversal */
    virtual void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbString_s {
        char* value;
    };
     
    //constructor.
    dtkStringCollection();

    //destructor
    virtual ~dtkStringCollection();

    //resize array
    _fbString_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, const char* key);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbString_s* Array;
};

#endif //DTKSTRINGCOLLECTION_H
