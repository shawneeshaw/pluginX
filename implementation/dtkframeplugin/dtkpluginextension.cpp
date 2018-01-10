#include "dtkpluginframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginExtension);

//-------------------------------------------------------------------------
// class dtkPluginExtension
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
void dtkPluginExtension::SetPath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) >= 0);
    //@@end preconditions

    if (this->extensionData.path != NULL) {
        delete[] this->extensionData.path;
        this->extensionData.path = NULL;
    }
    int slen = (int)strlen(path);
    this->extensionData.path = new char[slen+1];
    strcpy(this->extensionData.path, path);
}

//-------------------------------------------------------------------------
const char* dtkPluginExtension::GetPath() {
    return this->extensionData.path;
}

//-------------------------------------------------------------------------
void dtkPluginExtension::SetCodons(dtkPluginCodonCollection* codons) {
    //@@preconditions
    assert(codons != NULL);
    //@@end preconditions

    this->extensionData.codons = codons;
}

//-------------------------------------------------------------------------
dtkPluginCodonCollection* dtkPluginExtension::GetCodons() {
    return this->extensionData.codons;
}

//-------------------------------------------------------------------------
dtkPluginExtension::dtkPluginExtension() {
    memset(&this->extensionData, 0, sizeof(_fbExtension_s));
}

//-------------------------------------------------------------------------
dtkPluginExtension::~dtkPluginExtension() {
    if (this->extensionData.path != NULL) {
        delete[] this->extensionData.path;
        this->extensionData.path = NULL;
    }
    if (this->extensionData.codons) {
        this->extensionData.codons->Release();
        this->extensionData.codons = NULL;
    }
}
