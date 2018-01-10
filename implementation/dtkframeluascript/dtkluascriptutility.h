#ifndef _LUASCRIPTUTILITY_H
#define _LUASCRIPTUTILITY_H

/*--------------------------------------------------------------------------*/
/*                              Data Structures                             */
/*--------------------------------------------------------------------------*/

typedef struct lua_State lua_State;

/*--------------------------------------------------------------------------*/
/*                            Public Prototypes                             */    
/*--------------------------------------------------------------------------*/
class dtkLuaScriptUtilty {
    
public: //------------------------------------------
    static int GetInteger                 (lua_State *L, int index, int           &val);
    static int GetDouble                  (lua_State *L, int index, double        &val); 
    static int GetFloat                   (lua_State *L, int index, float         &val);
    static int GetString                  (lua_State *L, int index, const char   *&val);
    static int GetArrayInteger            (lua_State *L, int index, int          *&array);
    static int GetArrayDouble             (lua_State *L, int index, double       *&array); 
    static int GetArrayFloat              (lua_State *L, int index, float        *&array);
    static int GetArrayUnsignedInteger    (lua_State *L, int index, unsigned int *&array);
    static int GetArrayUnsignedChar       (lua_State *L, int index, unsigned char*&array);
    static int GetArrayString             (lua_State *L, int index, const char  **&array);
    static int GetVOID                    (lua_State *L, int index, void         *&val);
    
    static int SetRetInteger              (lua_State *L, int           val);
    static int SetRetDouble               (lua_State *L, double        val); 
    static int SetRetFloat                (lua_State *L, float         val);
    static int SetRetString               (lua_State *L, const char    *val);
    static int SetRetVOID                 (lua_State *L, void          *val);
    static int SetRetArrayInteger         (lua_State *L, int           *array, int size);
    static int SetRetArrayDouble          (lua_State *L, double        *array, int size); 
    static int SetRetArrayFloat           (lua_State *L, float         *array, int size);
    static int SetRetArrayUnsignedInteger (lua_State *L, unsigned int  *array, int size);
    static int SetRetArrayUnsignedChar    (lua_State *L, unsigned char *array, int size);
    static int SetRetArrayString          (lua_State *L, const char   **array, int size);

public://------------------------------------------
    static int FreeArray(void* array);
    
public: // ---------------------------------------
    dtkLuaScriptUtilty();
    ~ dtkLuaScriptUtilty(void);
};

#define LuaD_getInteger              dtkLuaScriptUtilty::GetInteger                
#define LuaD_getDouble               dtkLuaScriptUtilty::GetDouble                 
#define LuaD_getFloat                dtkLuaScriptUtilty::GetFloat                   
#define LuaD_getString               dtkLuaScriptUtilty::GetString                 
#define LuaD_getVoid                 dtkLuaScriptUtilty::GetVOID                 
#define LuaD_getArrayInteger         dtkLuaScriptUtilty::GetArrayInteger           
#define LuaD_getArrayDouble          dtkLuaScriptUtilty::GetArrayDouble            
#define LuaD_getArrayFloat           dtkLuaScriptUtilty::GetArrayFloat              
#define LuaD_getArrayUnsignedChar    dtkLuaScriptUtilty::GetArrayUnsignedChar      
#define LuaD_getArrayUnsignedInteger dtkLuaScriptUtilty::GetArrayUnsignedInteger
#define LuaD_getArrayString          dtkLuaScriptUtilty::GetArrayString

#define LuaD_retInteger              dtkLuaScriptUtilty::SetRetInteger             
#define LuaD_retDouble               dtkLuaScriptUtilty::SetRetDouble              
#define LuaD_retFloat                dtkLuaScriptUtilty::SetRetFloat               
#define LuaD_retString               dtkLuaScriptUtilty::SetRetString  
#define LuaD_retVoid                 dtkLuaScriptUtilty::SetRetVOID                            
#define LuaD_retArrayInteger         dtkLuaScriptUtilty::SetRetArrayInteger         
#define LuaD_retArrayDouble          dtkLuaScriptUtilty::SetRetArrayDouble          
#define LuaD_retArrayFloat           dtkLuaScriptUtilty::SetRetArrayFloat          
#define LuaD_retArrayUnsignedInteger dtkLuaScriptUtilty::SetRetArrayUnsignedInteger 
#define LuaD_retArrayUnsignedChar    dtkLuaScriptUtilty::SetRetArrayUnsignedChar    
#define LuaD_retArrayString          dtkLuaScriptUtilty::SetRetArrayString   

#define LuaD_freeArray               dtkLuaScriptUtilty::FreeArray

#endif // _LUASCRIPTUTILITY_H
