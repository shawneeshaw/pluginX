
#ifndef DTKPLUGIN_H
#define DTKPLUGIN_H

class dtkPlugin : public IPlugin, public dtkObject {

public:
    /** create instance */
    static dtkPlugin * New();

public:
    /** name */
    void  SetName(const char* name);
    const char* GetName();

    /** author */
    void  SetAuthor(const char* name);
    const char* GetAuthor();
    
    /** copyright */
    void  SetCopyright(const char* name);
    const char* GetCopyright();

    /** url */
    void  SetUrl(const char* name);
    const char* GetUrl();

    /** description */
    void  SetDescription(const char* name);
    const char* GetDescription();

    /** version */
    void  SetVersion(const char* name);
    const char* GetVersion();

    /** xml name */
    void  SetXmlName(const char* name);
    const char* GetXmlName();

    /** set requires lib name */
    void SetRequireLibs(dtkStringCollection* extensions);
    dtkStringCollection* GetRequireLibs();

    /** set dynamic dll name */
    void SetDynamicFactories(dtkStringCollection* extensions);
    dtkStringCollection* GetDynamicFactories();

    /** set zscript lib name */
    void SetZScriptLibs(dtkStringCollection* extensions);
    dtkStringCollection* GetZScriptLibs();

    /** extensions */
    void SetExtensions(dtkPluginExtensionCollection* extensions);
    dtkPluginExtensionCollection* GetExtensions();

public:
    /**set parent widget. */
    virtual void SetParent(dtkCompositePlugin* pcWidget);
    
    /**get composite Widget */
    virtual dtkCompositePlugin* GetParent();
    
    /** is composite or not. */
    virtual int IsComposite() { return 0; }

public:
    struct _fbPlugin_s {
        char* name;
        char* author;
        char* copyright;
        char* url;
        char* description;
        char* version;
        char* xmlname;
        void* userdata;
        dtkStringCollection* requires;
        dtkStringCollection* dllnames;
        dtkStringCollection* libnames;
        dtkCompositePlugin* parent;
        dtkPluginExtensionCollection* extensions;
    };
    
    //constructor. 1
    dtkPlugin();
    
    //constructor. 2
    dtkPlugin(dtkCompositePlugin* parent);

    //destructor.
    virtual ~dtkPlugin();

    //protected variables   
    _fbPlugin_s pluginData;
};

#endif //DTKPLUGIN_H
