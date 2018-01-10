#ifndef DTKPLUGINCODON_H
#define DTKPLUGINCODON_H

class TiXmlElement;
class dtkPluginCodon : public IPluginCodon, public dtkObject {

public:
    /** create instance */
    static dtkPluginCodon * New();

public:
    /** name */
    void  SetName(const char* name);
    const char* GetName();

    /** id */
    void  SetId(const char* id);
    const char* GetId();

    /** condition */
    void  SetCondition(const char* condition);
    const char* GetCondition();

    /** attribute */
    void  SetAttribute(const char* key, const char* val);
    const char* GetAttribute(const char* key);

    /** user data */
    void  SetUserData(void* userdata);
    void* GetUserData();

    /** value */
    void  SetXmlValue(const char* value);
    const char* GetXmlValue();
   
    /** plugin */
    void  SetPlugin(IPlugin* value);
    IPlugin* GetPlugin();

public:
    struct _fbCodon_s {
        char* id;
        char* name;
        char* condition;
        char* xmlvalue;
        void* userdata;
        dtkHashTableStringOneKey* attributes;
        dtkPlugin* plugin;
    };
    
    //constructor. 1
    dtkPluginCodon();
    
    //destructor.
    virtual ~dtkPluginCodon();

    //protected variables   
    _fbCodon_s codonData;
};

#endif //DTKPLUGINCODON_H
