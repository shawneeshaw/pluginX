// zpluginlib.cpp : Defines the entry point for the DLL application.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//local includes.
#include "dtkapplication.h"
#include "dtkcommonincludes.h"
#include "zpluginlib.h"

extern "C" {

//-----------------------------------------------------------------------------
// static variable declaration.
//-----------------------------------------------------------------------------
//
static dtkApplication * pZAppInstance = NULL;

//-----------------------------------------------------------------------------
//
//       System API
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int cpl_init() {
    //@@preconditions
    assert(pZAppInstance == NULL);
    //@@end preconditions

    pZAppInstance = dtkApplication::Instance();
    pZAppInstance->Initialize();
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_deInit() {
    //@@preconditions
    assert(pZAppInstance != NULL);
    //@@end preconditions

    pZAppInstance->Cleanup();
    pZAppInstance = NULL;
    dtkApplication::Delete();
    return 1;
}

//-----------------------------------------------------------------------------
//
//       Function API
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int cpl_luaSetVM(void* luaState) {
    //@@preconditions    
    assert(pZAppInstance != NULL);
    //@@end preconditions

    pZAppInstance->SetLuaState(luaState);
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_luaGetVM(void** luaState) {
    //@@preconditions    
    assert(pZAppInstance != NULL);
    //@@end preconditions
 
    void* _pState = 0;
    pZAppInstance->GetLuaState(_pState);
    assert(_pState != NULL);
    *luaState = _pState;
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_luaRunFile(const char* filename) {
    //@@preconditions    
    assert(filename != NULL);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    return pZAppInstance->GetLuaScriptProxy()->RunFile(filename);
}

//-----------------------------------------------------------------------------
int cpl_luaRunScript(const char* buffer) {
    //@@preconditions    
    assert(buffer != NULL);
    assert(strlen(buffer) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    return pZAppInstance->GetLuaScriptProxy()->RunString(buffer);
}

//-----------------------------------------------------------------------------
int cpl_luaIsConditionValid(const char* expression) {
    //@@preconditions
    assert(expression != NULL);
    //@@end preconditions

    return pZAppInstance->RunExpression(expression); 
}

//-----------------------------------------------------------------------------
int cpl_loadPlugins(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions
    
    pZAppInstance->LoadPlugins(path);
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_getPluginTree(IPluginTree** tree) {
    //@@preconditions    
    //@@end preconditions

    *tree = pZAppInstance->GetPluginProxy();
    return 1;
}

//-----------------------------------------------------------------------------
//
//       Class Factory API
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int cpl_createObject(const char* progId, void** ppv, int overrided) {
    //@@preconditions
    assert(progId != NULL);
    assert(strlen(progId) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    return pZAppInstance->GetCreator()->CreateObject(progId, ppv, overrided);
}

//-----------------------------------------------------------------------------
int cpl_loadClassOverrideInfo(const char* classinfoPath) {
    //@@preconditions
    assert(classinfoPath != NULL);
    assert(strlen(classinfoPath) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    pZAppInstance->LoadClassOverrideInfo(classinfoPath);
    return 1;
}
 
//-----------------------------------------------------------------------------
int cpl_addClassOverrideInfo(const char* classInfo, const char* classInfoOverride) {
    //@@preconditions
    assert(classInfo != NULL);
    assert(strlen(classInfo) > 0);
    assert(classInfoOverride != NULL);
    assert(strlen(classInfoOverride) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    return pZAppInstance->GetCreator()->InsertClassOverrideInfo(classInfo, classInfoOverride);
}

//-----------------------------------------------------------------------------
int cpl_removeClassOverrideInfo(const char* classInfo) {
    //@@preconditions
    assert(classInfo != NULL);
    assert(strlen(classInfo) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    return  pZAppInstance->GetCreator()->RemoveClassOverrideInfo(classInfo);
}

//-----------------------------------------------------------------------------
int cpl_addClassLoadFunction(IMPLEMENTPROXY_FUNC func) {
    //@@preconditions
    assert(pZAppInstance != NULL);
    //@@end preconditions

    int count = 0;
    ImplementationProxy* proxies = func(count);
    for (int j = 0; j < count; j++) {
        pZAppInstance->GetCreator()->InsertImplementationProxy(proxies[j]);
    }
    return count;
}

//-----------------------------------------------------------------------------
int cpl_removeClassLoadFunction(IMPLEMENTPROXY_FUNC func) {
    //@@preconditions
    assert(pZAppInstance != NULL);
    //@@end preconditions

    int count = 0;
    ImplementationProxy* proxies = func(count);
    for (int j = 0; j < count; j++) {
        pZAppInstance->GetCreator()->RemoveImplementationProxy(proxies[j]);
    }
    return count;
}

//-----------------------------------------------------------------------------
//
//       Service API
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int cpl_initializeServicesSubsystem(const char* servicesPath) {
    //@@preconditions
    assert(servicesPath != NULL);
    assert(strlen(servicesPath) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    pZAppInstance->InitializeServicesSubsystem(servicesPath);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_startAllServices() {
    //@@preconditions
    assert(pZAppInstance != NULL);
    //@@end preconditions

    pZAppInstance->StartAllServices();
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_unloadAllServices() {
    //@@preconditions
    assert(pZAppInstance != NULL);
    //@@end preconditions

    pZAppInstance->UnloadAllServices();
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_addService(const char* key, void* service, int priority) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(service != NULL);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    dtkService* _service = static_cast <dtkService*>(service);
    if (_service != NULL) {
        pZAppInstance->AddService(key, _service, priority);
    }
    return 0;
}
    
//-----------------------------------------------------------------------------
int cpl_removeService(void* service) {
    //@@preconditions
    assert(service != NULL);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    dtkService* _service = static_cast <dtkService*>(service);
    if (_service != NULL) {
        pZAppInstance->RemoveService(_service);
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_findService(const char* key, void** service) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(pZAppInstance != NULL);
    //@@end preconditions

    void*_service = 0;
    pZAppInstance->FindService(key, _service);
    *service = _service;
    return 0;
}

//-----------------------------------------------------------------------------
//Declaration "C" function
//-----------------------------------------------------------------------------
}
