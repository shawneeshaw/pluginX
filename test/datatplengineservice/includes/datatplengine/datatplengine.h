#ifndef DATATPLENGINEINTERFACE_H
#define DATATPLENGINEINTERFACE_H

#ifdef DATATPLENGINE_EXPORTS
#define DATATPLENGINE_API __declspec(dllexport)
#else
#define DATATPLENGINE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************\
 *
 *        System API
 *
\*****************************************************************************/
/** load data template engine */
int DATATPLENGINE_API DataTPLEngineLoad(void* luaState);

/** unload data template engine */
int DATATPLENGINE_API DataTPLEngineUnLoad();

/** register external application program */
int DATATPLENGINE_API DataTPLEngineRegisterAppProgram(char* appKey, char* appPath);

#ifdef __cplusplus
}
#endif

#endif //DATATPLENGINEINTERFACE_H
