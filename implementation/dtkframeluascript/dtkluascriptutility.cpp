#include <lua.hpp>
#include <stdlib.h>
#include <assert.h>
#include "dtkluascriptutility.h"

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetInteger(lua_State *L, int index, int &val) {
    //@@preconditions
    assert(L != NULL);
    //@@end preconditions

    if (!lua_isnumber(L, index)) {
        luaL_error(L, "incorrect argument to function 'get_numf'");
        return 0;
    }
    val = (int)lua_tonumber(L, index);  
    return 1;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetDouble(lua_State *L, int index, double &val) {
    //@@preconditions
    assert(L != NULL);
    //@@end preconditions

    if (!lua_isnumber(L, index)) {
        luaL_error(L, "incorrect argument to function 'get_numf'");
        return 0;
    }
    val = (double)lua_tonumber(L, index);  
    return 1;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetFloat(lua_State *L, int index, float &val) {
    //@@preconditions
    assert(L != NULL);
    //@@end preconditions

    if (!lua_isnumber(L, index)) {
        luaL_error(L, "incorrect argument to function 'get_numf'");
        return 0;
    }
    val = (float)lua_tonumber(L, index);    
    return 1;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetString(lua_State *L, int index, const char *&val) {
    //@@preconditions
    assert(L != NULL);
    //@@end preconditions

    if (!lua_isstring(L, index)) {
       luaL_error(L, "incorrect argument to function 'get_nums'");
       return 0;
    }
    const char *str = lua_tostring(L, index);
    assert(str != NULL);

    val = str;
    return 1;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetVOID(lua_State *L, int index, void  *&val) {
    //@@preconditions
    assert(L != NULL);
    //@@end preconditions

    if (!lua_isuserdata(L, index)) {
        luaL_error(L, "incorrect argument to function 'get_nums'");
        return 0;
    }
    void * pdata = (void*)lua_touserdata(L, index);
    assert(pdata != NULL);
    
    val = pdata;
    return 1;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetArrayInteger(lua_State *L, int index, int *&array) {
    /* get "table" table */
    lua_pushstring(L, "table");
    lua_gettable(L, LUA_GLOBALSINDEX);
    
    /* get "getn" entry */
    lua_pushstring(L, "getn");
    lua_gettable(L, -2);
    
    /* call it and get result */
    lua_pushvalue(L, index);  /* index of your table in the stack */
    lua_call(L, 1, 1);
    int n_elements = (int)lua_tonumber(L, -1);  /* store table size */
    lua_pop(L, 1);  /* pop table size */

    if (n_elements <= 0) {
        return 0;
    }

    array = (int *)malloc(n_elements * sizeof(int));
    int n = 0;
    for (;;) {
        lua_rawgeti(L, index, ++n);
        if (lua_isnil(L, -1)) break;
        (array)[n-1] = (int)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    assert(n == n_elements+1);
    return n_elements;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetArrayDouble(lua_State *L, int index, double *&array) {
    /* get "table" table */
    lua_pushstring(L, "table");
    lua_gettable(L, LUA_GLOBALSINDEX);
    
    /* get "getn" entry */
    lua_pushstring(L, "getn");
    lua_gettable(L, -2);
    
    /* call it and get result */
    lua_pushvalue(L, index);  /* index of your table in the stack */
    lua_call(L, 1, 1);
    int n_elements = (int)lua_tonumber(L, -1);  /* store table size */
    lua_pop(L, 1);  /* pop table size */

    if (n_elements <= 0) {
        return 0;
    }
    
    array = (double *)malloc(n_elements * sizeof(double));
    int n = 0;
    for (;;) {
        lua_rawgeti(L, index, ++n);
        if (lua_isnil(L, -1)) break;
        (array)[n-1] = (double)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    assert(n == n_elements+1);
    return n_elements;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetArrayFloat(lua_State *L, int index, float *&array) {
    /* get "table" table */
    lua_pushstring(L, "table");
    lua_gettable(L, LUA_GLOBALSINDEX);
    
    /* get "getn" entry */
    lua_pushstring(L, "getn");
    lua_gettable(L, -2);
    
    /* call it and get result */
    lua_pushvalue(L, index);  /* index of your table in the stack */
    lua_call(L, 1, 1);
    int n_elements = (int)lua_tonumber(L, -1);  /* store table size */
    lua_pop(L, 1);  /* pop table size */

    if (n_elements <= 0) {
        return 0;
    }
    
    array = (float *)malloc(n_elements * sizeof(float));
    int n = 0;
    for (;;) {
        lua_rawgeti(L, index, ++n);
        if (lua_isnil(L, -1)) break;
        (array)[n-1] = (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    assert(n == n_elements+1);
    return n_elements;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetArrayUnsignedInteger(lua_State *L, int index, unsigned int *&array) {
    /* get "table" table */
    lua_pushstring(L, "table");
    lua_gettable(L, LUA_GLOBALSINDEX);
    
    /* get "getn" entry */
    lua_pushstring(L, "getn");
    lua_gettable(L, -2);
    
    /* call it and get result */
    lua_pushvalue(L, index);  /* index of your table in the stack */
    lua_call(L, 1, 1);
    int n_elements = (int)lua_tonumber(L, -1);  /* store table size */
    lua_pop(L, 1);  /* pop table size */

    if (n_elements <= 0) {
        return 0;
    }
    
    array = (unsigned int *)malloc(n_elements * sizeof(unsigned int));
    int n = 0;
    for (;;) {
        lua_rawgeti(L, index, ++n);
        if (lua_isnil(L, -1)) break;
        (array)[n-1] = (unsigned int)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    assert(n == n_elements+1);
    return n_elements;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetArrayUnsignedChar(lua_State *L, int index, unsigned char *&array) {
    /* get "table" table */
    lua_pushstring(L, "table");
    lua_gettable(L, LUA_GLOBALSINDEX);
    
    /* get "getn" entry */
    lua_pushstring(L, "getn");
    lua_gettable(L, -2);
    
    /* call it and get result */
    lua_pushvalue(L, index);  /* index of your table in the stack */
    lua_call(L, 1, 1);
    int n_elements = (int)lua_tonumber(L, -1);  /* store table size */
    lua_pop(L, 1);  /* pop table size */

    if (n_elements <= 0) {
        return 0;
    }
    
    array = (unsigned char *)malloc(n_elements * sizeof(unsigned char));
    int n = 0;
    for (;;) {
        lua_rawgeti(L, index, ++n);
        if (lua_isnil(L, -1)) break;
        (array)[n-1] = (unsigned char)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    assert(n == n_elements+1);
    return n_elements;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::GetArrayString(lua_State *L, int index, const char **&array) {
    /* get "table" table */
    lua_pushstring(L, "table");
    lua_gettable(L, LUA_GLOBALSINDEX);
    
    /* get "getn" entry */
    lua_pushstring(L, "getn");
    lua_gettable(L, -2);
    
    /* call it and get result */
    lua_pushvalue(L, index);  /* index of your table in the stack */
    lua_call(L, 1, 1);
    int n_elements = (int)lua_tonumber(L, -1);  /* store table size */
    lua_pop(L, 1);  /* pop table size */

    if (n_elements <= 0) {
        return 0;
    }
    
    array = (const char **)malloc(n_elements * sizeof(char*));
    int n = 0;
    for (;;) {
        lua_rawgeti(L, index, ++n);
        if (lua_isnil(L, -1)) break;
        (array)[n-1] = (const char*)lua_tostring(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    assert(n == n_elements+1);
    return n_elements;
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetInteger(lua_State *L, int val) {
    lua_pushnumber(L, val);
    return 1;
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetDouble(lua_State *L, double val) {
    lua_pushnumber(L, val);
    return 1;
}

//----------------------------------------------------------------------------- 
int dtkLuaScriptUtilty::SetRetFloat(lua_State *L, float val) {
    lua_pushnumber(L, val);
    return 1;
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetString(lua_State *L, const char *val) {
    lua_pushstring(L, val);
    return 1;
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetVOID(lua_State *L, void *val) {
    lua_pushlightuserdata(L, val);
    return 1;
}

//----------------------------------------------------------------------------- 
static void set_field(lua_State *L, unsigned int index, lua_Number value) {
    lua_pushnumber(L, index);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

//----------------------------------------------------------------------------- 
static void set_field(lua_State *L, unsigned int index, const char* value) {
    lua_pushnumber(L, index);
    lua_pushstring(L, value);
    lua_settable(L, -3);
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetArrayInteger(lua_State *L, int *array, int size) {
    lua_newtable(L);    
    for(int i = 0; i < size; i++) {
        set_field(L, i+1, array[i]);
    }
    return 1; 
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetArrayDouble(lua_State *L, double *array, int size) {
    lua_newtable(L);    
    for(int i = 0; i < size; i++) {
        set_field(L, i+1, array[i]);
    }
    return 1;    
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetArrayFloat(lua_State *L, float *array, int size) {
    lua_newtable(L);    
    for(int i = 0; i < size; i++) {
        set_field(L, i+1, array[i]);
    }
    return 1; 
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetArrayUnsignedInteger(lua_State *L, unsigned int *array, int size) {
    lua_newtable(L);    
    for(int i = 0; i < size; i++) {
        set_field(L, i+1, array[i]);
    }
    return 1; 
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetArrayUnsignedChar(lua_State *L, unsigned char *array, int size) {
    lua_newtable(L);    
    for(int i = 0; i < size; i++) {
        set_field(L, i+1, array[i]);
    }
    return 1; 
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::SetRetArrayString(lua_State *L, const char **array, int size) {
    lua_newtable(L);    
    for(int i = 0; i < size; i++) {
        set_field(L, i+1, array[i]);
    }
    return 1; 
}

//-----------------------------------------------------------------------------
int dtkLuaScriptUtilty::FreeArray(void* array){
    //@@preconditions
    assert(array != NULL);
    //@@end preconditions

    free(array);
    return 0;
}
