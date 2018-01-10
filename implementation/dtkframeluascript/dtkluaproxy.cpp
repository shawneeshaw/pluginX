#include "dtkluascriptframeincludes.h"

class dtkLuaProxy::dtkImplemenation : public dtkLuaScriptProxy {
public:
    //initialize.
    void Initialize();
    
    //cleanup.
    void Cleanup();
        
    //execute file
    int RunFile(const char* fileName);

    //execute command  
    int RunString(const char* commandString);

    //register lib.
    int RegisterLib(lua_RegisterLib func);
    
    //register lib.
    int RegisterLib(const char* lua_lib);

public:
    //constructor
    dtkImplemenation();

    //destructor.
    ~dtkImplemenation();

    //protected variables.
    dtkLuaManager * LuaHandler;
    dtkLuaScript* luaScript;
};

//-----------------------------------------------------------------------------
dtkLuaProxy::dtkImplemenation::dtkImplemenation() {
    this->LuaHandler = new dtkLuaManager();
    this->luaScript = NULL;
}

//-----------------------------------------------------------------------------
dtkLuaProxy::dtkImplemenation::~dtkImplemenation() {
    //@@preconditions
    assert(this->luaScript == NULL);
    //@@end preconditions    

    if (this->LuaHandler != NULL) {
        delete this->LuaHandler;
        this->LuaHandler = NULL;
    }
}

//-----------------------------------------------------------------------------
int dtkLuaProxy::dtkImplemenation::RegisterLib(lua_RegisterLib func) {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    this->LuaHandler->RegisterLib(func);
    return 0;
}

//-----------------------------------------------------------------------------
int dtkLuaProxy::dtkImplemenation::RegisterLib(const char* lua_lib) {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    this->LuaHandler->RegisterLib(lua_lib);
    return 0;
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::dtkImplemenation::Initialize() {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    this->luaScript = this->LuaHandler->CreateScript();
    assert(this->luaScript != NULL);
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::dtkImplemenation::Cleanup() {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    if (this->luaScript != NULL) {
        delete this->luaScript;
        this->luaScript = NULL;
    }
}

//-----------------------------------------------------------------------------
int dtkLuaProxy::dtkImplemenation::RunString(const char* buffer) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(buffer != NULL);
    //@@end preconditions

    return this->luaScript->RunString((char*)buffer);
}

//-----------------------------------------------------------------------------
int dtkLuaProxy::dtkImplemenation::RunFile(const char* fname) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(fname != NULL);
    //@@end preconditions

    this->luaScript->RunFile((char*)fname);
    return 1;
}

//-----------------------------------------------------------------------------
// class dtkPostScriptProxy
//-----------------------------------------------------------------------------
//
dtkLuaProxy* dtkLuaProxy::New() {
    return new dtkLuaProxy;
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::DoInitialization() {
    //@@preconditions
    assert(this->scriptProxy == NULL);
    //@@end preconditions

    this->scriptProxy = new dtkImplemenation();
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::DoCleanup() {
    if (this->scriptProxy != NULL) {
        this->scriptProxy->Cleanup();
        delete this->scriptProxy;
        this->scriptProxy = NULL;
    }
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::CreateScriptContext() {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    this->scriptProxy->Initialize();
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::RegisterLib(lua_RegisterLib func) {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    this->scriptProxy->RegisterLib(func);
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::RegisterLib(const char* libname) {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    this->scriptProxy->RegisterLib(libname);
}

//-----------------------------------------------------------------------------
void* dtkLuaProxy::GetMainLuaState() {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    assert(this->scriptProxy->LuaHandler != NULL);
    //@@end preconditions

    return this->scriptProxy->LuaHandler->masterState;
}

//-----------------------------------------------------------------------------
void dtkLuaProxy::SetLuaState(void* data) {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    assert(this->scriptProxy->LuaHandler != NULL);
    //@@end preconditions

    this->scriptProxy->LuaHandler->SetLuaState(data);
}

//-----------------------------------------------------------------------------
dtkLuaScriptProxy* dtkLuaProxy::GetImplementation() {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    return this->scriptProxy;
}

//-----------------------------------------------------------------------------
dtkLuaProxy::dtkLuaProxy() {
    this->scriptProxy = NULL;
}

//-----------------------------------------------------------------------------
dtkLuaProxy::~dtkLuaProxy() {
    if (this->scriptProxy != NULL) {
        delete this->scriptProxy;
        this->scriptProxy = NULL;
    }
}
