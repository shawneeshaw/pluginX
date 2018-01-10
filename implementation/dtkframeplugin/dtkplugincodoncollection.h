#ifndef DTKPLUGINCODONCOLLECTION_H
#define DTKPLUGINCODONCOLLECTION_H

class dtkPluginCodonCollection: public dtkObject {

public:
    /** create instance */
    static dtkPluginCodonCollection * New();
    
public:
    /** allocate. */
    virtual int  Allocate(int sz, int ext);

    /** get size */
    virtual int  GetNumberOfItem();

    /** add item */
    virtual int  InsertNextItem(dtkPluginCodon* extension);
    
    /** remove item */
    virtual int  RemoveItem(dtkPluginCodon* extension);
    
    /** remove all */
    virtual int  RemoveAllItems();
    
    /** get next item */
    virtual int  GetNextItem(dtkPluginCodon*& extension);

    /** initial traversal */
    virtual void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbCodon_s {
        dtkPluginCodon* item;
    };
     
    //constructor.
    dtkPluginCodonCollection();

    //destructor
    virtual ~dtkPluginCodonCollection();

    //resize array
    _fbCodon_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, dtkPluginCodon* extension);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbCodon_s* Array;
};

#endif //DTKPLUGINCODONCOLLECTION_H
