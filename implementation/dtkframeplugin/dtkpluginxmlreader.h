#ifndef DTKPLUGINXMLREADER_H
#define DTKPLUGINXMLREADER_H

class TiXmlElement;
class dtkPluginXmlReader : public dtkObject {

public:
    /** create instance */
    static dtkPluginXmlReader * New();
    
    /** set plugin */
    virtual void SetPlugin(dtkPlugin* Plugin);

    /** set filename */
    virtual void SetXmlSource(const char* name);

    /** parse */
    virtual int Parse();

public:
    //constructor.
    dtkPluginXmlReader();

    //destructor
    virtual ~dtkPluginXmlReader();

    //parse runtime and extension.
    void ParseRequire(TiXmlElement* element);
    void ParseRuntime(TiXmlElement* element);
    void ParseZScript(TiXmlElement* element);
    void ParseExtensions(TiXmlElement* element);
    void ParseRuntimeAndExtension(TiXmlElement* element);
    void ParseAssembly(TiXmlElement* element, dtkStringCollection*& collection);
    void ParseCodonCollection(TiXmlElement* element, dtkPluginExtension* extension);

    //protected variables.
    dtkPlugin* Plugin;
    char* XmlSource;
};

#endif //DTKPLUGINXMLREADER_H
