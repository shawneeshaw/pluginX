#ifndef CPLSERVICESTRINGPARSERIMP_H
#define CPLSERVICESTRINGPARSERIMP_H

class IPluginTree;
class caxServiceDataTPLEngineImp : public caxServiceDataTPLEngine {

public:
    /** create instance */
    static caxServiceDataTPLEngineImp * New();

public:
    /** load service */
    virtual void InitializeService();

    /** unload service */
    virtual void UnloadService();

protected:    
    //constructor
    caxServiceDataTPLEngineImp() {}

    //destructor.
    virtual ~caxServiceDataTPLEngineImp() {}

    //register application by nest.
    void RegisterApp(IPluginTree* pluginTree, const char* path);
};

#endif //CPLSERVICESTRINGPARSERIMP_H
