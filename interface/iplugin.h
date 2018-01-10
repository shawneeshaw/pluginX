#ifndef DTKPLUGININTERFACE_H
#define DTKPLUGININTERFACE_H

class IPlugin {
public:
    /** name */
    virtual void  SetName(const char* name) = 0;
    virtual const char* GetName() = 0;

    /** author */
    virtual void  SetAuthor(const char* name) = 0;
    virtual const char* GetAuthor() = 0;
    
    /** copyright */
    virtual void  SetCopyright(const char* name) = 0;
    virtual const char* GetCopyright() = 0;

    /** url */
    virtual void  SetUrl(const char* name) = 0;
    virtual const char* GetUrl() = 0;

    /** description */
    virtual void  SetDescription(const char* name) = 0;
    virtual const char* GetDescription() = 0;

    /** version */
    virtual void  SetVersion(const char* name) = 0;
    virtual const char* GetVersion() = 0;

    /** xml name */
    virtual void  SetXmlName(const char* name)= 0;
    virtual const char* GetXmlName() = 0;
};

#endif //DTKPLUGININTERFACE_H
