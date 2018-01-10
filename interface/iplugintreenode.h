#ifndef DTKPLUGINTREENODEINTERFACE_H
#define DTKPLUGINTREENODEINTERFACE_H

class IPluginTreePath;
class IPluginCodon;
class IPluginTreeNode {
public:
    /** name */
    virtual void SetName(const char* name) = 0;
    virtual const char* GetName() = 0;

    /** path */
    virtual void SetPath(const char* path) = 0;
    virtual const char* GetPath() = 0;

    /** user data */
    virtual void  SetUserData(const void* userdata) = 0;
    virtual const void* GetUserData()= 0;

    /** codon */
    virtual void SetCodon(IPluginCodon* codon) = 0;
    virtual IPluginCodon* GetCodon()= 0;
    
    /** parent. */
    virtual void SetParent(IPluginTreePath* parent) = 0;
    virtual IPluginTreePath* GetParent() = 0;

    /** is composite or not. */
    virtual int IsComposite() = 0;
};

#endif //DTKPLUGINTREENODEINTERFACE_H
