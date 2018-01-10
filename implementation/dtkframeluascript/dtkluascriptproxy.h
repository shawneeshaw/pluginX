#ifndef DTKLUASCRIPTPROXY_H
#define DTKLUASCRIPTPROXY_H

class dtkLuaScriptProxy {
public:
    virtual int RunFile(const char* fileName) = 0;
    virtual int RunString(const char* commandString) = 0;
    virtual int RegisterLib(const char* lua_fname) = 0;
};

#endif //DTKLUASCRIPTPROXY_H
