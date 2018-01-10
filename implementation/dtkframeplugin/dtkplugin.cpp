#include "dtkpluginframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPlugin);

//-------------------------------------------------------------------------
// class dtkPlugin
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
void  dtkPlugin::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    if (this->pluginData.name != NULL) {
        delete[] this->pluginData.name;
        this->pluginData.name = NULL;
    }
    int slen = (int)strlen(name);
    this->pluginData.name = new char[slen+1];
    strcpy(this->pluginData.name, name);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetName() {
    return this->pluginData.name;
}

//-------------------------------------------------------------------------
void  dtkPlugin::SetAuthor(const char* author) {
    //@@preconditions
    assert(author != NULL);
    assert(strlen(author) >= 0);
    //@@end preconditions

    if (this->pluginData.author != NULL) {
        delete[] this->pluginData.author;
        this->pluginData.author = NULL;
    }
    int slen = (int)strlen(author);
    this->pluginData.author = new char[slen+1];
    strcpy(this->pluginData.author, author);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetAuthor() {
    return this->pluginData.author;
}

//-------------------------------------------------------------------------
void  dtkPlugin::SetCopyright(const char* copyright) {
    //@@preconditions
    assert(copyright != NULL);
    assert(strlen(copyright) >= 0);
    //@@end preconditions

    if (this->pluginData.copyright != NULL) {
        delete[] this->pluginData.copyright;
        this->pluginData.copyright = NULL;
    }
    int slen = (int)strlen(copyright);
    this->pluginData.copyright = new char[slen+1];
    strcpy(this->pluginData.copyright, copyright);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetCopyright() {
    return this->pluginData.copyright;
}

//-------------------------------------------------------------------------
void  dtkPlugin::SetUrl(const char* url) {
    //@@preconditions
    assert(url != NULL);
    assert(strlen(url) >= 0);
    //@@end preconditions

    if (this->pluginData.url != NULL) {
        delete[] this->pluginData.url;
        this->pluginData.url = NULL;
    }
    int slen = (int)strlen(url);
    this->pluginData.url = new char[slen+1];
    strcpy(this->pluginData.url, url);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetUrl() {
    return this->pluginData.url;
}

//-------------------------------------------------------------------------
void  dtkPlugin::SetDescription(const char* description) {
    //@@preconditions
    assert(description != NULL);
    assert(strlen(description) >= 0);
    //@@end preconditions

    if (this->pluginData.description != NULL) {
        delete[] this->pluginData.description;
        this->pluginData.description = NULL;
    }
    int slen = (int)strlen(description);
    this->pluginData.description = new char[slen+1];
    strcpy(this->pluginData.description, description);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetDescription() {
    return this->pluginData.description;        
}

//-------------------------------------------------------------------------
void  dtkPlugin::SetVersion(const char* version) {
    //@@preconditions
    assert(version != NULL);
    assert(strlen(version) >= 0);
    //@@end preconditions

    if (this->pluginData.version != NULL) {
        delete[] this->pluginData.version;
        this->pluginData.version = NULL;
    }
    int slen = (int)strlen(version);
    this->pluginData.version = new char[slen+1];
    strcpy(this->pluginData.version, version);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetVersion() {
    return this->pluginData.version;
}

//-------------------------------------------------------------------------
void  dtkPlugin::SetXmlName(const char* xmlname) {
    //@@preconditions
    assert(xmlname != NULL);
    assert(strlen(xmlname) >= 0);
    //@@end preconditions

    if (this->pluginData.xmlname != NULL) {
        delete[] this->pluginData.xmlname;
        this->pluginData.xmlname = NULL;
    }
    int slen = (int)strlen(xmlname);
    this->pluginData.xmlname = new char[slen+1];
    strcpy(this->pluginData.xmlname, xmlname);
}

//-------------------------------------------------------------------------
const char* dtkPlugin::GetXmlName() {
    return this->pluginData.xmlname;
}

//-------------------------------------------------------------------------
void dtkPlugin::SetParent(dtkCompositePlugin* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    this->pluginData.parent = parent;
}
   
//-------------------------------------------------------------------------
dtkCompositePlugin* dtkPlugin::GetParent() {
    return this->pluginData.parent;
}

//-------------------------------------------------------------------------
void dtkPlugin::SetExtensions(dtkPluginExtensionCollection* extensions) {
    //@@preconditions
    assert(extensions != NULL);
    //@@end preconditions

    this->pluginData.extensions = extensions;
}

//-------------------------------------------------------------------------
dtkPluginExtensionCollection* dtkPlugin::GetExtensions() {
    return this->pluginData.extensions;    
}

//-------------------------------------------------------------------------
void dtkPlugin::SetRequireLibs(dtkStringCollection* names) {
    //@@preconditions
    assert(names != NULL);
    //@@end preconditions

    this->pluginData.requires = names;
}

//-------------------------------------------------------------------------
dtkStringCollection* dtkPlugin::GetRequireLibs() {
    return this->pluginData.requires;   
}

//-------------------------------------------------------------------------
void dtkPlugin::SetDynamicFactories(dtkStringCollection* names) {
    //@@preconditions
    assert(names != NULL);
    //@@end preconditions

    this->pluginData.dllnames = names;
}

//-------------------------------------------------------------------------
dtkStringCollection* dtkPlugin::GetDynamicFactories() {
    return this->pluginData.dllnames;   
}

//-------------------------------------------------------------------------
void dtkPlugin::SetZScriptLibs(dtkStringCollection* names) {
    //@@preconditions
    assert(names != NULL);
    //@@end preconditions

    this->pluginData.libnames = names;
}

//-------------------------------------------------------------------------
dtkStringCollection* dtkPlugin::GetZScriptLibs() {
    return this->pluginData.libnames;   
}

//-------------------------------------------------------------------------
dtkPlugin::dtkPlugin() {
    memset(&this->pluginData, 0, sizeof(_fbPlugin_s));
}

//-------------------------------------------------------------------------
dtkPlugin::dtkPlugin(dtkCompositePlugin* parent) {
    memset(&this->pluginData, 0, sizeof(_fbPlugin_s));
    this->pluginData.parent = parent;
}

//-------------------------------------------------------------------------
dtkPlugin::~dtkPlugin() {
    if (this->pluginData.name != NULL) {
        delete[] this->pluginData.name;
        this->pluginData.name = NULL;
    }
    if (this->pluginData.author != NULL) {
        delete[] this->pluginData.author;
        this->pluginData.author = NULL;
    }
    if (this->pluginData.copyright != NULL) {
        delete[] this->pluginData.copyright;
        this->pluginData.copyright = NULL;
    }
    if (this->pluginData.url != NULL) {
        delete[] this->pluginData.url;
        this->pluginData.url = NULL;
    }
    if (this->pluginData.description != NULL) {
        delete[] this->pluginData.description;
        this->pluginData.description = NULL;
    }
    if (this->pluginData.version != NULL) {
        delete[] this->pluginData.version;
        this->pluginData.version = NULL;
    }
    if (this->pluginData.xmlname) {
        delete[] this->pluginData.xmlname;
        this->pluginData.xmlname = 0;
    }
    if (this->pluginData.extensions != NULL) {
        this->pluginData.extensions->Release();
        this->pluginData.extensions = 0;
    }
    if (this->pluginData.dllnames != NULL) {
        this->pluginData.dllnames->Release();
        this->pluginData.dllnames = 0;
    }
    if (this->pluginData.requires != NULL) {
        this->pluginData.requires->Release();
        this->pluginData.requires = 0;
    }
    if (this->pluginData.libnames != NULL) {
        this->pluginData.libnames->Release();
        this->pluginData.libnames = 0;
    }
}
