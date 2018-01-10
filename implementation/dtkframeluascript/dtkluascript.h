/*--------------------------------------------------------------------------*/
/*                           Compilation Control                            */
/*--------------------------------------------------------------------------*/
#ifndef _LUASCRIPT_H
#define _LUASCRIPT_H

/*--------------------------------------------------------------------------*/
/*                            Defined Constants                             */
/*--------------------------------------------------------------------------*/
typedef enum luaScriptStateTag {
    LSS_WAITFRAME,
    LSS_WAITTIME,
    LSS_RUNNING,
    LSS_NOTLOADED,
    LSS_DONE
} LUASCRIPTSTATE;

/*--------------------------------------------------------------------------*/
/*                              Data Structures                             */
/*--------------------------------------------------------------------------*/
class dtkLuaManager;
typedef struct lua_State lua_State;

class dtkLuaScript {
public: // ---------------------------------------
    dtkLuaScript(dtkLuaManager* mgr);
    ~ dtkLuaScript(void);

    void CreateThread(void);    
    void RunFile(char* fileName);
    void CallFn(char* fnName, int iParam);
    void AbortWait(void);

    int  RunString(char* commandString);
    dtkLuaScript* Update(float elapsedSec);
public: //------------------------------------------
    dtkLuaManager* manager; // dtkLuaManager object that created this script
    dtkLuaScript* next;
    LUASCRIPTSTATE state;   // are we waiting, not loaded yet, etc.
    float waitTimestamp;    // time to wake up
    float time; // current time   
    int waitFrame;  // number of frames to wait
private:    // ---------------------------------------
    lua_State*  threadState;
    char lastErrorString[256];
    void ResumeScript(float param);
    void FormatError(void);
    void OutputError(char* strType);
};

#endif // _LUASCRIPT_H
