#ifndef DTKPLUGINEXTENSIONCOLLECTION_H
#define DTKPLUGINEXTENSIONCOLLECTION_H

class dtkPluginExtensionCollection : public dtkObject {

public:
    /** create instance */
    static dtkPluginExtensionCollection * New();
    
public:
    /** allocate. */
    virtual int  Allocate(int sz, int ext);

    /** get size */
    virtual int  GetNumberOfItem();

    /** add item */
    virtual int  InsertNextItem(dtkPluginExtension* extension);
    
    /** remove item */
    virtual int  RemoveItem(dtkPluginExtension* extension);
    
    /** remove all */
    virtual int  RemoveAllItems();
    
    /** get next item */
    virtual int  GetNextItem(dtkPluginExtension*& extension);

    /** initial traversal */
    virtual void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbExtension_s {
        dtkPluginExtension* item;
    };
     
    //constructor.
    dtkPluginExtensionCollection();

    //destructor
    virtual ~dtkPluginExtensionCollection();

    //resize array
    _fbExtension_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, dtkPluginExtension* extension);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbExtension_s* Array;
};

#endif //DTKPLUGINEXTENSIONCOLLECTION_H
