// signal header has been included
#ifndef _LUAMANAGER_H
#define _LUAMANAGER_H

/*--------------------------------------------------------------------------*/
/*                              Data Structures                             */
/*--------------------------------------------------------------------------*/
class dtkLuaScript;
typedef struct lua_State lua_State;

typedef void (*lua_RegisterLib) (lua_State* l);

class dtkLuaManager {
public: // ---------------------------------------
    dtkLuaManager(void);
    ~ dtkLuaManager(void);
    void SetLuaState(void* data);
    void RegisterLib(const char* lua_fname);
    void RegisterLib(lua_RegisterLib func);
    void UnlinkScript(dtkLuaScript* s);
    void Update(float elapsedSec);
    int  NumScripts(void);
    dtkLuaScript* CreateScript(void);
    lua_State*  masterState; 
    int masterStateLocal;
private:    // ---------------------------------------
    dtkLuaScript*   head;
};
#endif // _LUAMANAGER_H
