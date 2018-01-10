#ifndef DTKPLUGINCODONINTERFACE_H
#define DTKPLUGINCODONINTERFACE_H

class IPluginCodon {
public:
    /** name */
    virtual void  SetName(const char* name) = 0; 
    virtual const char* GetName() = 0;

    /** id */
    virtual void  SetId(const char* id) = 0;
    virtual const char* GetId() = 0;

    /** condition */
    virtual void  SetCondition(const char* condition) = 0;
    virtual const char* GetCondition() = 0;

    /** attributes */
    virtual void  SetAttribute(const char* key, const char* val) = 0;
    virtual const char* GetAttribute(const char* key) = 0;

    /** value */
    virtual void  SetXmlValue(const char* value) = 0;
    virtual const char* GetXmlValue() = 0;

    /** user data */
    virtual void  SetUserData(void* userdata) = 0;
    virtual void* GetUserData() = 0;
   
    /** plugin */
    virtual void  SetPlugin(IPlugin* value) = 0;
    virtual IPlugin* GetPlugin() = 0;
};

#endif //DTKPLUGINCODONINTERFACE_H
