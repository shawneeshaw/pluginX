#ifndef DTKPLUGINTREEMAP_H
#define DTKPLUGINTREEMAP_H

class dtkPluginTreeMap : public dtkObject {

public:
    /** create instance */
    static dtkPluginTreeMap * New();

public:
    /** initialize */
    virtual int DoInitialization();

    /** cleanup */
    virtual int DoCleanup();
   
    /** get node in specific path */
    dtkPluginTreePath* GetPath(const char* path);
    
    /** create path. */
    dtkPluginTreePath* CreatePath(const char* path);

public:
    // constructor.
    dtkPluginTreeMap();

    // destructor
    virtual ~dtkPluginTreeMap();

    // protected varaibles.
    dtkPluginTreePath* rootPath;

    //create path.
    dtkPluginTreePath* CreatePath(dtkPluginTreePath* path, const char* path_name);
};

#endif //DTKPLUGINTREEMAP_H
