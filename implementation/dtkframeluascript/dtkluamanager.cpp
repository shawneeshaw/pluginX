/*--------------------------------------------------------------------------*/
/*                              Include Files                               */
/*--------------------------------------------------------------------------*/
#include <lua.hpp>
#include <stdio.h>
#include <assert.h>
#include "dtkluascript.h"
#include "dtkluamanager.h"

//-----------------------------------------------------------------------------
dtkLuaManager::dtkLuaManager() {
    this->masterStateLocal = 1;
    this->masterState = lua_open();
    if (this->masterState) {
        // open any auxiliary libraries we may need
        luaL_openlibs(this->masterState);
    }
    head = NULL;
}

//-----------------------------------------------------------------------------
dtkLuaManager::~dtkLuaManager() {
    // destroy all children scripts
    dtkLuaScript* s = head;
    while (s) {
        // save the next pointer in case the script is deleted
        dtkLuaScript* next = s->next;
        delete s;
        s = next;
    }
    // Verify the stack
    if (this->masterStateLocal) {
        lua_close(this->masterState);
    }
}

//-----------------------------------------------------------------------------
void dtkLuaManager::SetLuaState(void* data) {
    //@@preconditions
    assert(data != NULL);
    //@@end preconditions

    if (this->masterStateLocal) {
        lua_close(this->masterState);        
    }

    this->masterStateLocal = 0;
    this->masterState =(lua_State*)data;
}

//-----------------------------------------------------------------------------
void dtkLuaManager::RegisterLib(lua_RegisterLib func) {
    //@@preconditions
    assert(this->masterState != NULL);
    //@@end preconditions

    func(this->masterState);
}

//-----------------------------------------------------------------------------
void dtkLuaManager::RegisterLib(const char* lua_fname) {
    //@@preconditions
    assert(this->masterState != NULL);
    //@@end preconditions

    if (luaL_loadfile(this->masterState, lua_fname) || lua_pcall(this->masterState, 0, 0, 0)) {
        printf("error: %s", lua_tostring(this->masterState, -1));
    }
}

//-----------------------------------------------------------------------------
dtkLuaScript* dtkLuaManager::CreateScript() {
    // create a script object
    dtkLuaScript* s = new dtkLuaScript(this);

    // tell the script object who its manager is
    s->manager = this;

    // link the new script into the list
    s->next = head;
    head = s;
    return(s);
}

//-----------------------------------------------------------------------------
void dtkLuaManager::UnlinkScript(dtkLuaScript* s) {
    // if s is at the head, simply unlink it
    if (head == s) {
        head = s->next;
        return;
    }

    // find previous link
    dtkLuaScript* prev = head;
    while (prev) {
        if (prev->next == s) {
            prev->next = s->next;
            return;
        }
        prev = prev->next;
    }
}

//-----------------------------------------------------------------------------
void dtkLuaManager::Update(float elapsedSec) {
    dtkLuaScript* s = head;
    while (s) {
        s = s->Update(elapsedSec);
    }
}
