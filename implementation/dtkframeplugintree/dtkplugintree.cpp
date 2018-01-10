#include "dtkplugintreeframeincludes.h"

//local includes.
#include <lua.hpp>
#include "../dtktinyxml/tinyxml.h"

typedef struct lua_State lua_State;

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginTree);

//-----------------------------------------------------------------------------
// class dtkPluginTree
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int dtkPluginTree::SetLuaState(void* luaState) {
    //@@preconditions
    assert(luaState != NULL);
    //@@end preconditions

    this->pLuaState = luaState;
    return 1;
}

//-----------------------------------------------------------------------------
int dtkPluginTree::Parse(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(this->PluginManager != NULL);
    assert(this->PathManager != NULL);
    //@@end preconditions

    //parse plugin in the specific path.
    this->PluginManager->Parse(path);

    //load resources accordingly.
    this->LoadLibRequired();
    this->LoadDllRuntimes();
    this->LoadZScriptPackage();

    //assembly everyting together.
    this->AssemblyExtensions();
    return 1;
}

//-----------------------------------------------------------------------------
static int RegisterLib(void* lua_state, const char* lua_fname) {
    //@@preconditions
    assert(lua_fname != NULL);
    assert(strlen(lua_fname) > 0);
    assert(lua_state != NULL);
    //@@end preconditions

    lua_State* state = (lua_State*)lua_state;
    assert(state != NULL);
    if (luaL_loadfile(state, lua_fname) || lua_pcall(state, 0, 0, 0)) {
        printf("error: %s", lua_tostring(state, -1));
    }
    return 1;
}

//-----------------------------------------------------------------------------
int dtkPluginTree::LoadLuaScriptPackage() {
    //@@preconditions
    assert(this->pLuaState != NULL);
    //@@end preconditions
    
    for (int j = 0; j < this->ZScriptResource.libCount; j++) {
        RegisterLib(this->pLuaState, this->ZScriptResource.libHandlers[j]);
    }
    return 0;
}

//-----------------------------------------------------------------------------
int dtkPluginTree::LoadLuaRuntimePackage() {
    //@@preconditions
    assert(this->pLuaState != NULL);
    //@@end preconditions

    typedef int (* CreatFuncPtr) (lua_State* L);    
    for (int j = 0; j < this->DLLResource.libCount; j++) {
        void* lib = this->DLLResource.libHandlers[j];
        if (lib) {
            CreatFuncPtr loadfunction = (CreatFuncPtr) dtkDynamicLoader::GetSymbolAddress(lib, "luaopen_plugin");
            if (loadfunction) {
                loadfunction((lua_State *)this->pLuaState);
            }
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
int dtkPluginTree::LoadClassCreatorRuntimePackage(dtkCreator* pCreator) {
    //@@preconditions
    assert(pCreator != NULL);
    //@@end preconditions

    typedef dtkImplementationProxy* (* CreatFuncPtr) (int&);
    int sum = 0;
    for (int j = 0; j < this->DLLResource.libCount; j++) {
        void* lib = this->DLLResource.libHandlers[j];
        if (lib) {
            CreatFuncPtr loadfunction = (CreatFuncPtr) dtkDynamicLoader::GetSymbolAddress(lib, "CoGetImplementationProxy");
            if (loadfunction) {
                int count = 0;
                dtkImplementationProxy* proxies = loadfunction(count);
                for (int i = 0; i < count; i++) {
                    pCreator->InsertImplementationProxy(proxies[i]);
                    sum++;
                }
            }
        }
    }
    return sum;
}

//-----------------------------------------------------------------------------
IPluginTreePath* dtkPluginTree::GetTreePath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(path[0] != '\0');
    assert(this->PathManager != NULL);
    //@@end preconditons

    return this->PathManager->GetPath(path);
}

//-----------------------------------------------------------------------------
IPluginTreePath* dtkPluginTree::CreateTreePath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(path[0] != '\0');
    assert(this->PathManager != NULL);
    //@@end preconditons

    return this->PathManager->CreatePath(path);
}

//-----------------------------------------------------------------------------
void dtkPluginTree::AssemblyExtensions() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    //@@end preconditions

    dtkCompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPlugins();
    if (count == 0) {
        return;
    }
    this->GetNestSubItemExtensions(root);
}

//-----------------------------------------------------------------------------
void dtkPluginTree::LoadLibRequired() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    assert(this->DLLResource.libHandlers == NULL);
    //@@end preconditions

    dtkCompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPluginsRequireLib();
    if (count == 0) {
        return;
    }

    this->DLLRequired.libCount = 0;
    this->DLLRequired.libSize  = count;
    this->DLLRequired.libHandlers = new void* [count];
    assert(this->DLLRequired.libHandlers != NULL);

    this->GetNestSubItemLibRequired(root);
}

//-----------------------------------------------------------------------------
void dtkPluginTree::LoadDllRuntimes() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    assert(this->DLLResource.libHandlers == NULL);
    //@@end preconditions

    dtkCompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPluginsDLL();
    if (count == 0) {
        return;
    }

    this->DLLResource.libCount = 0;
    this->DLLResource.libSize = count;
    this->DLLResource.libHandlers = new void* [count];
    assert(this->DLLResource.libHandlers != NULL);

    this->GetNestSubItemDllRuntimes(root);
}

//-----------------------------------------------------------------------------
void dtkPluginTree::LoadZScriptPackage() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    assert(this->ZScriptResource.libHandlers == NULL);
    //@@end preconditions

    dtkCompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPluginsZScript();
    if (count == 0) {
        return;
    }

    this->ZScriptResource.libCount = 0;
    this->ZScriptResource.libSize  = count;
    this->ZScriptResource.libHandlers = new char* [count];
    assert(this->ZScriptResource.libHandlers != NULL);

    this->GetNestSubItemScriptName(root);
}

//-----------------------------------------------------------------------------
static int vtkNameIsSharedLibrary(const char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    char* ret = strstr(copy, dtkDynamicLoader::LibExtension());
    if   (ret != NULL) {
        if (strlen(ret) == strlen(dtkDynamicLoader::LibExtension())) {
            delete [] copy;
            return 1;
        }
    }
    delete [] copy;
    return 0;
}

//-----------------------------------------------------------------------------
static int vtkNameIsScriptLibrary(const char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    char* ret = strstr(copy, ".lua");
    if   (ret != NULL) {
        if (strlen(ret) == strlen(".lua")) {
            delete [] copy;
            return 1;
        }
    }
    delete [] copy;
    return 0;
}

//-----------------------------------------------------------------------------
static char* CreateFullPath(const char* path, const char* file) {
    //@@preconditions
    assert(path != NULL);
    assert(file != NULL);
    //@@end preconditions

    int lenpath = static_cast<int>(strlen(path));
    char* ret = new char[lenpath + strlen(file)+2];
    const char sep = '/';
    // make sure the end of path is a separator
    strcpy(ret, path);
    if (ret[lenpath-1] != sep) {
        ret[lenpath] = sep;
        ret[lenpath+1] = 0;
    }
    strcat(ret, file);
    return ret;
}

//-----------------------------------------------------------------------------
void dtkPluginTree::GetNestSubItemLibRequired(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemLibRequired((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkStringCollection* collection = sub_plugin->GetRequireLibs();
            if (collection == NULL) {
                continue;
            }
            const char* path = sub_plugin->GetParent()->GetName();
            if (path == NULL) {
                continue;
            }
            const char* name = NULL;
            for (collection->InitTraversal(); collection->GetNextItem(name);) {
                if (vtkNameIsSharedLibrary(name)) {
                    char* fullpath = CreateFullPath(path, name);
                    dtkLibHandle lib = dtkDynamicLoader::OpenLibrary(fullpath);
                    if(lib) {
                        assert(this->DLLRequired.libCount < this->DLLRequired.libSize); 
                        this->DLLRequired.libHandlers[this->DLLRequired.libCount++] = lib;
                    }
                    delete [] fullpath;
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void dtkPluginTree::GetNestSubItemDllRuntimes(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemDllRuntimes((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkStringCollection* collection = sub_plugin->GetDynamicFactories();
            if (collection == NULL) {
                continue;
            }
            const char* path = sub_plugin->GetParent()->GetName();
            if (path == NULL) {
                continue;
            }            
            const char* name = NULL;
            for (collection->InitTraversal(); collection->GetNextItem(name);) {
                if (vtkNameIsSharedLibrary(name)) {
                    char* fullpath = CreateFullPath(path, name);
                    dtkLibHandle lib = dtkDynamicLoader::OpenLibrary(fullpath);
                    if(lib) {
                        //coclass.
                        {
                            typedef dtkImplementationProxy* (* CreatFuncPtr) (int&);
                            CreatFuncPtr loadfunction = (CreatFuncPtr) dtkDynamicLoader::GetSymbolAddress(lib, "CoGetImplementationProxy");
                            if (loadfunction) {
                                assert(this->DLLResource.libCount < this->DLLResource.libSize); 
                                this->DLLResource.libHandlers[this->DLLResource.libCount++] = lib;
                            }
                        }
                        //lua components.
                        {
                            typedef int (* CreatFuncPtr) (lua_State* L);
                            CreatFuncPtr loadfunction = (CreatFuncPtr) dtkDynamicLoader::GetSymbolAddress(lib, "luaopen_plugin");
                            if (loadfunction) {
                                assert(this->DLLResource.libCount < this->DLLResource.libSize); 
                                this->DLLResource.libHandlers[this->DLLResource.libCount++] = lib;
                            }
                        }
                    }
                    delete [] fullpath;
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void dtkPluginTree::GetNestSubItemScriptName(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemScriptName((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkStringCollection* collection = sub_plugin->GetZScriptLibs();
            if (collection == NULL) {
                continue;
            }
            const char* path = sub_plugin->GetParent()->GetName();
            if (path == NULL) {
                continue;
            }
            const char* name = NULL;
            for (collection->InitTraversal(); collection->GetNextItem(name);) {
                if (vtkNameIsScriptLibrary(name)) {
                    char* fullpath = CreateFullPath(path, name);
                    FILE* fp = fopen(fullpath, "r");
                    if (fp != NULL) {
                        assert(this->ZScriptResource.libCount < this->ZScriptResource.libSize); 
                        this->ZScriptResource.libHandlers[this->ZScriptResource.libCount++] = fullpath;
                        fclose(fp);
                        continue;
                    }
                    delete[] fullpath;
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void dtkPluginTree::GetNestSubItemExtensions(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemExtensions((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkPluginExtensionCollection* extensions = sub_plugin->GetExtensions();
            if (extensions != NULL) {
                dtkPluginExtension* extension = 0;
                for (extensions->InitTraversal(); extensions->GetNextItem(extension); ) {
                    if (extension) {
                        const char* path = extension->GetPath();
                        if (path != NULL) {
                            dtkPluginTreePath* pluginPath = this->PathManager->CreatePath(path);
                            this->AddExtensionIntoPath(extension, pluginPath, sub_plugin);
                        }                        
                    }
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void dtkPluginTree::AddExtensionIntoPath(dtkPluginExtension* extension, dtkPluginTreePath* path, dtkPlugin* plugin) {
    //@@preconditions
    assert(extension != NULL);
    assert(plugin != NULL);
    assert(path != NULL);    
    //@@end preconditions

    dtkPluginCodonCollection* codons = extension->GetCodons();
    if (codons == NULL) {
        return;
    }

    dtkPluginCodon* codon = 0;
    for (codons->InitTraversal(); codons->GetNextItem(codon); ) {
        if (codon == NULL) {
            continue;
        }
        codon->SetPlugin(plugin);
        IPluginTreeNode* node = path->GetItem(codon);
        if (node == NULL) {
            node = new dtkPluginTreeNode(path);
            node->SetCodon(codon);
            path->InsertNextItem(node);
        }        
    }   
}

//-----------------------------------------------------------------------------
void dtkPluginTree::UnLoadDynamicFactories() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    //@@end preconditions

    //dll resources.
    {
        for (int i = 0; i < this->DLLResource.libCount; i++) {
            void* lib = this->DLLResource.libHandlers[i];
            if (lib == 0) {
                continue;
            }
            dtkDynamicLoader::CloseLibrary(reinterpret_cast<dtkLibHandle>(lib));
        }
    }
    //required dll..
    {
        for (int i = 0; i < this->DLLRequired.libCount; i++) {
            void* lib = this->DLLRequired.libHandlers[i];
            if (lib == 0) {
                continue;
            }
            dtkDynamicLoader::CloseLibrary(reinterpret_cast<dtkLibHandle>(lib));
        }
    }
}

//-----------------------------------------------------------------------------
dtkPluginTree::dtkPluginTree() {
    this->PluginManager = dtkPluginManager::New();
    this->PathManager = dtkPluginTreeMap::New();
    this->pLuaState = NULL;
    this->DLLRequired.libCount = 0;
    this->DLLRequired.libHandlers = NULL;
    this->DLLResource.libCount = 0;
    this->DLLResource.libHandlers = NULL;
    this->ZScriptResource.libCount = 0;
    this->ZScriptResource.libHandlers = NULL;
}

//-----------------------------------------------------------------------------
dtkPluginTree::~dtkPluginTree() {
    if (this->PathManager != NULL) {
        this->PathManager->Release();
    }
    if (this->PluginManager != NULL) {
        this->PluginManager->Release();
    }
    if (this->DLLResource.libHandlers) {
        delete[] this->DLLResource.libHandlers;
        this->DLLResource.libHandlers = NULL;
    }
    if (this->ZScriptResource.libHandlers) {
        for (int i = 0; i < this->ZScriptResource.libCount; i++) {
            if (this->ZScriptResource.libHandlers[i]) {
                delete[] this->ZScriptResource.libHandlers[i];
            }            
        }
        delete[] this->ZScriptResource.libHandlers;
        this->ZScriptResource.libHandlers = NULL;
    }
}
