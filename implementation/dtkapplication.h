#ifndef DTKAPPLICATION_H
#define DTKAPPLICATION_H

class IPluginTree;
class dtkCreator;
class dtkLuaProxy;
class dtkLuaScriptProxy;
class dtkPluginTree;
class dtkService;
class dtkServiceManager;
class dtkApplication {
public:
    /** create function */
    static dtkApplication * Instance();

    /** release object. */
    static void Delete();

	/** set application */
	static void SetApplication(dtkApplication* app);

public:
    /** initialize. */
    int Initialize();

    /** cleanup. */
    int Cleanup();

    /** set lua VM */
    int SetLuaState(void* luaState);

    /** get lua VM */
    int GetLuaState(void*& luaState);

    /** load plugin */
    int LoadPlugins(const char* path);
    
    /** run expression*/
    int RunExpression(const char* expression);

public:    
    /** add service */
    void AddService(const char* key, dtkService* service, int priority);
    
    /** remove service */
    void RemoveService(dtkService* service);

    /** initialize services on specific path*/
    void InitializeServicesSubsystem(const char* servicesPath);

    /** start all services */
    void StartAllServices();

    /** unload all services */
    void UnloadAllServices();

    /** find specific service */
    void FindService(const char* key, void*& service);

public:
    /** load class info */
    void LoadClassOverrideInfo(const char* classinfoPath);

public:
    /** get creator */
    dtkCreator* GetCreator();

    /** get plugin tree proxy */
    IPluginTree* GetPluginProxy();

    /** get lua script proxy */
    dtkLuaScriptProxy* GetLuaScriptProxy();
    
protected:
    // constructor 
    dtkApplication();

    // destructor 
    virtual ~dtkApplication();

    //protected functions.
    void LoadServiceNested(const char* path);  //load service nested.
    void LoadClassOverrideInfoNested(const char* path); //load class override info nested.

    //protected variables.
    dtkServiceManager* pServiceManager;
    dtkPluginTree* pluginTree;   
    dtkLuaProxy* pLuaProxy;
    dtkCreator* pObjectCreator;
private:
    /** singleton instance */
    static dtkApplication * instance;
};

#endif //DTKAPPLICATION_H
