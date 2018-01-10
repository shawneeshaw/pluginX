#ifndef DTKPLUGINCOMPOSITE_H
#define DTKPLUGINCOMPOSITE_H

/**
 * @stereotype container 
 */
class dtkCompositePlugin : public dtkPlugin {

public:
    /** create instance */
    static dtkCompositePlugin * New();

public:
    /** allocate. */
    virtual int Allocate(int sz, int ext);

    /** if is composite */
    virtual int IsComposite();

    /** operator += */
    dtkCompositePlugin& operator+=(dtkPlugin* plugin);

    /** operator -= */
    dtkCompositePlugin& operator-=(dtkPlugin* plugin);

    /** insert Widget */
    virtual int InsertNextItem(dtkPlugin* plugin);
    
    /** remove Widget */
    virtual int RemoveItem(dtkPlugin* plugin);
    
    /** remove all Widget */
    virtual int RemoveAllItems();

    /** get number of plugins. */
    virtual int GetNumberOfPlugins();
    
    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPlugins();

    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPluginsRequireLib();

    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPluginsDLL();

    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPluginsZScript();

    /** get specific position plugin */
    virtual dtkPlugin* GetPlugin(int subID);

public:    
    //constructor
    dtkCompositePlugin();

    //constructor
    dtkCompositePlugin(dtkCompositePlugin* plugin);
    
    //destructor
    virtual ~dtkCompositePlugin();

protected:        
    //inner structure
    struct _fbPluginItem_s {
        dtkPlugin* PluginItem;
        int resourceId;
    };
     
    //resize array
    _fbPluginItem_s* Reallocate(int size);

    //insert at the specific position.
    void InsertItem(int pos, dtkPlugin* plugin);

    //get number of nest action
    int GetNestSubItem(dtkCompositePlugin* plugin);
    int GetNestSubItemDLL(dtkCompositePlugin* plugin);
    int GetNestSubItemZScript(dtkCompositePlugin* plugin);    
    int GetNestSubItemRequireLib(dtkCompositePlugin* plugin);

    //protected variables
    _fbPluginItem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

//-------------------------------------------------------------------------
inline dtkCompositePlugin& dtkCompositePlugin::operator+=(dtkPlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    this->InsertNextItem(plugin);
    return *this;
}

//-------------------------------------------------------------------------
inline dtkCompositePlugin& dtkCompositePlugin::operator-=(dtkPlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    this->RemoveItem(plugin);
    return *this;
}

//-------------------------------------------------------------------------
inline int dtkCompositePlugin::IsComposite() {
    return 1;
}

//-------------------------------------------------------------------------
inline int dtkCompositePlugin::GetNumberOfPlugins() {
    return this->MaxId + 1;
}

//-------------------------------------------------------------------------
inline dtkPlugin* dtkCompositePlugin::GetPlugin(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfPlugins());
    assert(this->Array != NULL);
    //@@end preconditons
    
    return this->Array[pos].PluginItem;    
}

#endif //DTKPLUGINCOMPOSITE_H
