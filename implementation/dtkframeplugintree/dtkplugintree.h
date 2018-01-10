#ifndef DTKPLUGINTREE_H
#define DTKPLUGINTREE_H

class dtkLuaScriptProxy;
class dtkCreator;
class dtkPluginTree : public dtkObject, public IPluginTree {
public:
    /** create instance */
    static dtkPluginTree * New();

public:
    /** parse */
    virtual int Parse(const char* path);

    /** set lua VM */
    virtual int SetLuaState(void* luaState);

    /** load lua script files */
    virtual int LoadLuaScriptPackage();

    /** load lua runtime dlls */
    virtual int LoadLuaRuntimePackage();

    /** load class creator runtime dlls */
    virtual int LoadClassCreatorRuntimePackage(dtkCreator* pCreator);

public:
    /** get node in specific path */
    virtual IPluginTreePath* GetTreePath(const char* path);

    /** create path. */
    virtual IPluginTreePath* CreateTreePath(const char* path);

public:
    //inner structure.
    struct _fbPluginDLL_s {
        int libCount;
        int libSize;
        void** libHandlers;
    };

    //inner structure.
    struct _fbPluginZScript_s {
        int libCount;
        int libSize;
        char** libHandlers;
    };

    //constructor.
    dtkPluginTree();

    //destructor
    virtual ~dtkPluginTree();

    //protected variables.
    void* pLuaState;
    _fbPluginDLL_s DLLRequired;
    _fbPluginDLL_s DLLResource;
    _fbPluginZScript_s ZScriptResource;

    //plugin manager.
    dtkPluginManager* PluginManager;
    dtkPluginTreeMap* PathManager;

    //load dynamic factories.    
    void LoadLibRequired();
    void LoadDllRuntimes();
    void UnLoadDynamicFactories();
    void LoadZScriptPackage();
    void AssemblyExtensions();

    //get number of nest action
    void GetNestSubItemLibRequired(dtkCompositePlugin* plugin);
    void GetNestSubItemDllRuntimes(dtkCompositePlugin* plugin);
    void GetNestSubItemScriptName (dtkCompositePlugin* plugin);
    void GetNestSubItemExtensions (dtkCompositePlugin* plugin);

    //link.
    void AddExtensionIntoPath(dtkPluginExtension* extension, dtkPluginTreePath* path, dtkPlugin* plugin);
};

#endif //DTKPLUGINMANAGER_H
