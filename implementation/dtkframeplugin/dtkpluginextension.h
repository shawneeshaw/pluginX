#ifndef DTKPLUGINEXTENSION_H
#define DTKPLUGINEXTENSION_H

class dtkPluginExtension: public dtkObject {

public:
    /** create instance */
    static dtkPluginExtension * New();

public:
    /** path */
    void SetPath(const char* name);
    const char* GetPath();
   
    /** codons */
    void SetCodons(dtkPluginCodonCollection* codons);
    dtkPluginCodonCollection* GetCodons();

public:
    struct _fbExtension_s {
        char* path;
        dtkPluginCodonCollection* codons;
    };
    
    //constructor. 1
    dtkPluginExtension();
    
    //destructor.
    virtual ~dtkPluginExtension();

    //protected variables   
    _fbExtension_s extensionData;
};

#endif //DTKPLUGINEXTENSION_H
