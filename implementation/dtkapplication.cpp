#include <lua.hpp>
#include "dtkapplication.h"

//local includes...
#include "dtkcommonincludes.h"

//-----------------------------------------------------------------------------
// class dtkApplication
//-----------------------------------------------------------------------------
//
dtkApplication * dtkApplication::instance = NULL;

//-----------------------------------------------------------------------------
dtkApplication * dtkApplication::Instance() {
    if (dtkApplication::instance == NULL) {
        dtkApplication::instance = new dtkApplication;
    }
    return dtkApplication::instance;
}

//-----------------------------------------------------------------------------
void dtkApplication::Delete() {
    if (dtkApplication::instance) {
        delete dtkApplication::instance;
        dtkApplication::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
void dtkApplication::SetApplication(dtkApplication* app) {
    dtkApplication::instance = app;
}

//-----------------------------------------------------------------------------
dtkCreator* dtkApplication::GetCreator() {
    return this->pObjectCreator;
}

//-----------------------------------------------------------------------------
IPluginTree* dtkApplication::GetPluginProxy() {
    return this->pluginTree;
}

//-----------------------------------------------------------------------------
dtkLuaScriptProxy* dtkApplication::GetLuaScriptProxy() {
    //@@preconditions
    assert(this->pLuaProxy  != NULL);
    //@@end preconditions

    return this->pLuaProxy->GetImplementation();
}

//-----------------------------------------------------------------------------
int dtkApplication::Initialize() {    
    //@@preconditions
    assert(this->pLuaProxy  != NULL);
    assert(this->pluginTree != NULL);
    //@@end preconditions

    this->pLuaProxy->DoInitialization();
    this->pLuaProxy->CreateScriptContext();

    //set default lua state.
    this->pluginTree->SetLuaState(this->pLuaProxy->GetMainLuaState());
    return 1;
}

//-----------------------------------------------------------------------------
int dtkApplication::Cleanup() {
    //@@preconditions
    assert(this->pLuaProxy != NULL);
    //@@end preconditions

    this->pLuaProxy->DoCleanup();

    dtkObjectFactory::UnRegisterAllFactories();
    dtkObjectFactory::DeInit();
    return 1;
}

//-----------------------------------------------------------------------------
int dtkApplication::SetLuaState(void* luaState) {
    //@@preconditions
    assert(luaState != NULL);
    assert(this->pLuaProxy != NULL);
    assert(this->pluginTree != NULL);
    //@@end preconditions

    this->pLuaProxy->SetLuaState(luaState);
    return this->pluginTree->SetLuaState(luaState);    
}

//-----------------------------------------------------------------------------
int dtkApplication::GetLuaState(void*& luaState) {
    //@@preconditions
    assert(this->pLuaProxy != NULL);
    //@@end preconditions

    luaState = this->pLuaProxy->GetMainLuaState();
    return 0;
}

//-----------------------------------------------------------------------------
int dtkApplication::LoadPlugins(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(this->pluginTree != NULL);
    assert(this->pObjectCreator != NULL);
    //@@end preconditions

    if (dtkDirectory::FileIsDirectory(path) == 0) {
        return 0;
    }

    this->pluginTree->Parse(path);
    this->pluginTree->LoadClassCreatorRuntimePackage(this->pObjectCreator);
    this->pluginTree->LoadLuaRuntimePackage();
    this->pluginTree->LoadLuaScriptPackage();
    return 1;
}

//-----------------------------------------------------------------------------
int dtkApplication::RunExpression(const char* expression) {
    //@@preconditions
    assert(expression != NULL);
    //@@end preconditions

    void* _pState = 0;
    this->GetLuaState(_pState);
    assert(_pState != NULL);
    lua_State* L = (lua_State*)_pState;
    dtkString code;
    code += "function xyz0x1973() ";
    code += "return ";
    code += expression;
    code += ";";
    code += "end";
    luaL_loadstring(L, code.c_str()); // execute code
    lua_pcall(L,0,0,0);
    lua_getglobal(L, "xyz0x1973"); // get function
    int ret = -1;
    if (lua_pcall(L, 0, 1, 0) == 0) {
        ret = lua_toboolean(L, -1);
    }
    int n = lua_gettop(L);
    lua_pop(L, n);
    return ret;    
}

//-----------------------------------------------------------------------------
void dtkApplication::AddService(const char* key, dtkService* service, int priority) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(service != NULL);
    assert(this->pServiceManager != NULL);
    //@@end preconditions
    
    this->pServiceManager->AddService(key, service, priority);
}

//-----------------------------------------------------------------------------
void dtkApplication::RemoveService(dtkService* service) {
    //@@preconditions
    assert(service != NULL);
    assert(this->pServiceManager != NULL);
    //@@end preconditions

    this->pServiceManager->RemoveService(service);
}

//-----------------------------------------------------------------------------
void dtkApplication::InitializeServicesSubsystem(const char* servicesPath) {
    //@@preconditions
    assert(servicesPath != NULL);
    assert(strlen(servicesPath) > 0);
    assert(this->pServiceManager != NULL);
    //@@end preconditions

    //load service path..
    this->LoadServiceNested(servicesPath);
}

//-----------------------------------------------------------------------------
void dtkApplication::LoadServiceNested(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(this->pluginTree != NULL);
    assert(this->pServiceManager != NULL);
    assert(this->pObjectCreator != NULL);
    //@@end preconditions

    IPluginTreePath* treepath = this->pluginTree->GetTreePath(path);
    if (treepath == NULL) {
        return;
    }
    int numItem = treepath->GetNumberOfItems();
    for (int i = 0; i < numItem; i++) {
        IPluginTreeNode* node = treepath->GetItem(i);
        if (node->IsComposite()) {
            const char* path = node->GetPath();
            assert(path != NULL);           
            this->LoadServiceNested(path);
        }
        else {
            IPluginCodon* codon = node->GetCodon();
            assert(codon != NULL);

            const char* name = codon->GetName();
            if (strcmp(name, "SERVICE") == 0) {
                const char* id = codon->GetId();
                assert(id != NULL);
                const char* coclass = codon->GetAttribute("class");
                assert(coclass != NULL);
                const char* priority = codon->GetAttribute("priority");
                void* ppv= NULL;
                this->pObjectCreator->CreateObject(coclass, &ppv);
                if (ppv != NULL) {
                    if (priority == NULL) {
                        dtkService* service = static_cast <dtkService*>(ppv);
                        this->pServiceManager->AddService(id, service);   
                    }
                    else {
                        int _priority = atoi(priority);
                        dtkService* service = static_cast <dtkService*>(ppv);
                        this->pServiceManager->AddService(id, service, _priority);   
                    }                
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
void dtkApplication::StartAllServices() {
    //@@preconditions
    assert(this->pServiceManager != NULL);
    //@@end preconditions

    this->pServiceManager->InitializeAllServices();
}

//-----------------------------------------------------------------------------
void dtkApplication::UnloadAllServices() {
    //@@preconditions
    assert(this->pServiceManager != NULL);
    //@@end preconditions

    this->pServiceManager->UnloadAllServices();
}

//-----------------------------------------------------------------------------
void dtkApplication::FindService(const char* key, void*& service) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(this->pServiceManager != NULL);
    //@@end preconditions

    dtkService* _service = NULL;
    this->pServiceManager->GetService(key, _service);
    service = _service;
}

//-----------------------------------------------------------------------------
void dtkApplication::LoadClassOverrideInfo(const char* classinfoPath) {
    //@@preconditions
    assert(classinfoPath != NULL);
    assert(strlen(classinfoPath) > 0);
    assert(this->pServiceManager != NULL);
    //@@end preconditions

    //load service path..
    this->LoadClassOverrideInfoNested(classinfoPath);
}

//-----------------------------------------------------------------------------
void dtkApplication::LoadClassOverrideInfoNested(const char* path) {
    //@@preconditions
    assert(pluginTree != NULL);
    assert(path != NULL);
    assert(this->pluginTree != NULL);
    assert(this->pServiceManager != NULL);
    assert(this->pObjectCreator != NULL);
    //@@end preconditions

    IPluginTreePath* treepath = this->pluginTree->GetTreePath(path);
    if (treepath == NULL) {
        return;
    }
    int numItem = treepath->GetNumberOfItems();
    for (int i = 0; i < numItem; i++) {
        IPluginTreeNode* node = treepath->GetItem(i);
        if (node->IsComposite()) {
            const char* path = node->GetPath();
            assert(path != NULL);           
            this->LoadClassOverrideInfoNested(path);
        }
        else {
            IPluginCodon* codon = node->GetCodon();
            assert(codon != NULL);
            const char* name = codon->GetName();
            if (strcmp(name, "OVERRIDE") == 0) {
                const char* id = codon->GetId();
                assert(id != NULL);
                const char* coclass = codon->GetAttribute("class");
                assert(coclass != NULL);
                this->pObjectCreator->InsertClassOverrideInfo(id, coclass);
            }
        }
    }
}

//-----------------------------------------------------------------------------
dtkApplication::dtkApplication() {    
    this->pServiceManager = dtkServiceManager::New();
    this->pObjectCreator = dtkCreator::New();
    this->pluginTree = new dtkPluginTree;
    this->pLuaProxy = dtkLuaProxy::New();  
    dtkApplication::SetApplication(this);
}

//-----------------------------------------------------------------------------
dtkApplication::~dtkApplication() {
    if (this->pServiceManager != NULL) {
        this->pServiceManager->Release();
        this->pServiceManager = NULL;
    }
    if (this->pObjectCreator != NULL) {
        this->pObjectCreator->Release();
        this->pObjectCreator = NULL;
    }
    if (this->pLuaProxy != NULL) {
        this->pLuaProxy->Delete();
        this->pLuaProxy = NULL;
    }
    if (this->pluginTree != NULL) {
        this->pluginTree->Release();
        this->pluginTree = NULL;
    }
}
