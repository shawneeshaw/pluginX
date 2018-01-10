#ifndef DTKPLUGINMANAGER_H
#define DTKPLUGINMANAGER_H

class dtkPluginManager: public dtkObject {
public:
    /** create instance */
    static dtkPluginManager * New();

public:
    /** initialize */
    virtual int DoInitialization();

    /** cleanup */
    virtual int DoCleanup();
    
    /** parse */
    virtual int Parse(const char* path);

    /** get root path */
    virtual dtkCompositePlugin* GetRootPath();

public:
    // constructor.
    dtkPluginManager();

    // destructor
    virtual ~dtkPluginManager();

    // protected varaibles.
    dtkCompositePlugin* rootPluginPath;

    // parse plugin 
    int ParseInPath(dtkCompositePlugin* plugins, const char* path);
    int ParsePlugin(dtkCompositePlugin* plugins, const char* name);
};

#endif //DTKPLUGINMANAGER_H
