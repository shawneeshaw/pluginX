#ifndef DTKLUAPROXY_H
#define DTKLUAPROXY_H

class dtkLuaScriptProxy;
class dtkLuaProxy {
public:
    /** create instance */
    static dtkLuaProxy* New();

    virtual void Delete() { delete this; }
public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

    /** set lua state */
    virtual void SetLuaState(void* data);

    /** create script context */
    virtual void CreateScriptContext();

    /** register lib. */
    virtual void RegisterLib(lua_RegisterLib func);
    
    /** register lib. */
    virtual void RegisterLib(const char* libname);

    /** get main lua state */
    virtual void* GetMainLuaState();

public:
    /** get implementation */
    dtkLuaScriptProxy* GetImplementation();

protected:        
    //constructor.
    dtkLuaProxy();

    //destructor
    virtual ~dtkLuaProxy();

    //protected variables.
    class dtkImplemenation;
    dtkImplemenation * scriptProxy;
};

#endif //DTKLUAPROXY_H
