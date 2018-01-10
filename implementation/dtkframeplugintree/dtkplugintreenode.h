#ifndef DTKPLUGINTREENODE_H
#define DTKPLUGINTREENODE_H

class dtkPluginCodon;
class dtkPluginTreeNode: public IPluginTreeNode, public dtkObject {

public:
    /** create instance */
    static dtkPluginTreeNode * New();

public:
    /** name */
    virtual void  SetName(const char* name);
    virtual const char* GetName();

    /** path */
    virtual void  SetPath(const char* path);
    virtual const char* GetPath();

    /** user data */
    virtual void  SetUserData(const void* userdata);
    virtual const void* GetUserData();

    /** codon */
    virtual void  SetCodon(IPluginCodon* codon);
    virtual IPluginCodon* GetCodon();

    /**set parent widget. */
    virtual void  SetParent(IPluginTreePath* parent);
    virtual IPluginTreePath* GetParent();
    
    /** is composite or not. */
    virtual int  IsComposite() { return 0; }

public:
    //inner structure.
    struct _fbNode_s {
        char* name;
        char* path;
        void* data;
        dtkPluginCodon* codon;
        dtkPluginTreePath* parent;
    };

    //constructor. 1
    dtkPluginTreeNode();
    
    //constructor. 2
    dtkPluginTreeNode(dtkPluginTreePath* parent);

    //destructor.
    virtual ~dtkPluginTreeNode();

    //protected variables   
    _fbNode_s nodeData;
};

#endif //DTKPLUGINTREENODE_H
