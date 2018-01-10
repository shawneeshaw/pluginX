#ifndef DTKPLUGINTREEPATH_H
#define DTKPLUGINTREEPATH_H

class dtkPluginTreePath : public IPluginTreePath, public dtkPluginTreeNode {
public:
    /** create instance */
    static dtkPluginTreePath * New();

public:
    /** name */
    virtual void  SetName(const char* name);
    virtual const char* GetName();

    /** path */
    virtual void  SetPath(const char* path);
    virtual const char* GetPath();

    /** user data */
    virtual void  SetUserData(const void* userdata);
    virtual const void* GetUserData();

    /** codon */
    virtual void  SetCodon(IPluginCodon* codon);
    virtual IPluginCodon* GetCodon();

    /**set parent widget. */
    virtual void SetParent(IPluginTreePath* parent);
    virtual IPluginTreePath* GetParent();

public:
    /** allocate. */
    virtual int Allocate(int sz, int ext);

    /** if is composite */
    virtual int IsComposite();

    /** insert node */
    virtual int InsertNextItem(IPluginTreeNode* node);
    
    /** remove node */
    virtual int RemoveItem(IPluginTreeNode* node);
    
    /** remove all node */
    virtual int RemoveAllItems();

    /** get number of node. */
    virtual int GetNumberOfItems();
    
    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestItems();

    /** get specific position plugin */
    virtual IPluginTreeNode* GetItem(int subID);

    /** get specific plugin by name*/
    virtual IPluginTreeNode* GetItem(char* subID);

    /** get specific plugin by codon*/
    virtual IPluginTreeNode* GetItem(IPluginCodon* subID);

public:    
    //constructor
    dtkPluginTreePath();

    //constructor
    dtkPluginTreePath(dtkPluginTreePath* plugin);
    
    //destructor
    virtual ~dtkPluginTreePath();

    /** operator += */
    dtkPluginTreePath& operator+=(dtkPluginTreeNode* node);

    /** operator -= */
    dtkPluginTreePath& operator-=(dtkPluginTreeNode* node);

    /** get specific position plugin */
    virtual dtkPluginTreeNode* GetItemA(int subID);

    /** get specific plugin by name*/
    virtual dtkPluginTreeNode* GetItemA(char* subID);

protected:        
    //inner structure
    struct _fbNodetem_s {
        dtkPluginTreeNode* Item;
        int resourceId;
    };
     
    //resize array
    _fbNodetem_s* Reallocate(int size);

    //insert at the specific position.
    void InsertItem(int pos, dtkPluginTreeNode* node);

    //get number of item (nest mode)
    int GetNestSubItem(dtkPluginTreePath* node);

    //protected variables
    _fbNodetem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

//-------------------------------------------------------------------------
inline dtkPluginTreePath& dtkPluginTreePath::operator+=(dtkPluginTreeNode* node) {
    //@@preconditions
    assert(node != NULL);
    //@@end preconditions

    this->InsertNextItem(node);
    return *this;
}

//-------------------------------------------------------------------------
inline dtkPluginTreePath& dtkPluginTreePath::operator-=(dtkPluginTreeNode* node) {
    //@@preconditions
    assert(node != NULL);
    //@@end preconditions

    this->RemoveItem(node);
    return *this;
}

//-------------------------------------------------------------------------
inline int dtkPluginTreePath::IsComposite() {
    return 1;
}

//-------------------------------------------------------------------------
inline int dtkPluginTreePath::GetNumberOfItems() {
    return this->MaxId + 1;
}

//-------------------------------------------------------------------------
inline IPluginTreeNode* dtkPluginTreePath::GetItem(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfItems());
    assert(this->Array != NULL);
    //@@end preconditons
    
    return this->Array[pos].Item;    
}

#endif //DTKPLUGINTREEPATH_H
