#ifndef CPLUGINLIBINTERFACE_H
#define CPLUGINLIBINTERFACE_H

#ifdef libplugin_EXPORTS
#define CPLUGINLIBAPI __declspec(dllexport)
#else
#define CPLUGINLIBAPI __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************\
*
*       System API
*
\*****************************************************************************/

/** System: plugin system initialize */
int CPLUGINLIBAPI cpl_init();

/** System: plugin system cleanup */
int CPLUGINLIBAPI cpl_deInit();

/*****************************************************************************\
*
*       Script API
*
\*****************************************************************************/

/** Function: set lua VM handle */
int CPLUGINLIBAPI cpl_luaSetVM(void* luaState);

/** Function: get lua VM handle */
int CPLUGINLIBAPI cpl_luaGetVM(void** luaState);

/** Function: run lua script file*/
int CPLUGINLIBAPI cpl_luaRunFile(const char* fileName);

/** Function: run lua script buffer*/
int CPLUGINLIBAPI cpl_luaRunScript(const char* buffer);

/** Function: run condition string*/
int CPLUGINLIBAPI cpl_luaIsConditionValid(const char* condition);

/*****************************************************************************\
*
*       Function API
*
\*****************************************************************************/

/** Function: load plugin */
int CPLUGINLIBAPI cpl_loadPlugins(const char* path);

/** Function: get plugin tree*/
int CPLUGINLIBAPI cpl_getPluginTree(IPluginTree** tree);


/*****************************************************************************\
*
*       Class Factory API
*
\*****************************************************************************/

/** Function: load class info in specific path.*/
int CPLUGINLIBAPI cpl_loadClassOverrideInfo(const char* path);

/** Function: create object.*/
int CPLUGINLIBAPI cpl_createObject(const char* classId, void** ppv, int overrided);

/** Function: add class override info */
int CPLUGINLIBAPI cpl_addClassOverrideInfo(const char* classInfo, const char* classInfoOverride);

/** Function: add class functor.*/
int CPLUGINLIBAPI cpl_addClassLoadFunction(IMPLEMENTPROXY_FUNC func);

/*****************************************************************************\
*
*       Service API
*
\*****************************************************************************/

/** Function: initialize services on specific path*/
int CPLUGINLIBAPI cpl_initializeServicesSubsystem(const char* servicesPath);

/** Function: start all services */
int CPLUGINLIBAPI cpl_startAllServices();

/** Function: unload all services */
int CPLUGINLIBAPI cpl_unloadAllServices();

/** Function: add service. */
int CPLUGINLIBAPI cpl_addService(const char* key, void* service, int priority);
    
/** Function: remove service. */
int CPLUGINLIBAPI cpl_removeService(void* service);

/** Function: find specific service */
int CPLUGINLIBAPI cpl_findService(const char* key, void** service);


#ifdef __cplusplus
}
#endif

#endif //CPLUGINLIBINTERFACE_H
