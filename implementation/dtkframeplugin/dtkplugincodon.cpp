#include "dtkpluginframeincludes.h"
#include "../dtktinyxml/tinyxml.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginCodon);

//-------------------------------------------------------------------------
// class dtkPluginCodon
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
void dtkPluginCodon::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    if (this->codonData.name != NULL) {
        delete[] this->codonData.name;
        this->codonData.name = NULL;
    }
    int slen = (int)strlen(name);
    this->codonData.name = new char[slen+1];
    strcpy(this->codonData.name, name);
}

//-------------------------------------------------------------------------
const char* dtkPluginCodon::GetName() {
    return this->codonData.name;
}

//-------------------------------------------------------------------------
void dtkPluginCodon::SetId(const char* id) {
    //@@preconditions
    assert(id != NULL);
    assert(strlen(id) >= 0);
    //@@end preconditions

    if (this->codonData.id != NULL) {
        delete[] this->codonData.id;
        this->codonData.id = NULL;
    }
    int slen = (int)strlen(id);
    this->codonData.id = new char[slen+1];
    strcpy(this->codonData.id, id);
}

//-------------------------------------------------------------------------
const char* dtkPluginCodon::GetId() {
    return this->codonData.id;
}

//-------------------------------------------------------------------------
void dtkPluginCodon::SetCondition(const char* condition) {
    //@@preconditions
    assert(condition != NULL);
    assert(strlen(condition) >= 0);
    //@@end preconditions

    if (this->codonData.condition != NULL) {
        delete[] this->codonData.condition;
        this->codonData.condition = NULL;
    }
    int slen = (int)strlen(condition);
    this->codonData.condition = new char[slen+1];
    strcpy(this->codonData.condition, condition);
}

//-------------------------------------------------------------------------
const char* dtkPluginCodon::GetCondition() {
    return this->codonData.condition;
}

//-------------------------------------------------------------------------
void dtkPluginCodon::SetXmlValue(const char* value) {
    //@@preconditions
    assert(value != NULL);
    assert(strlen(value) >= 0);
    //@@end preconditions

    if (this->codonData.xmlvalue != NULL) {
        delete[] this->codonData.xmlvalue;
        this->codonData.xmlvalue = NULL;
    }
    int slen = (int)strlen(value);
    this->codonData.xmlvalue = new char[slen+1];
    strcpy(this->codonData.xmlvalue, value);
}

//-------------------------------------------------------------------------
const char* dtkPluginCodon::GetXmlValue() {
    return this->codonData.xmlvalue;
}

//-------------------------------------------------------------------------
void dtkPluginCodon::SetUserData(void* userdata) {
    this->codonData.userdata = userdata;
}

//-------------------------------------------------------------------------
void* dtkPluginCodon::GetUserData() {
    return this->codonData.userdata;
}

//-------------------------------------------------------------------------
void dtkPluginCodon::SetPlugin(IPlugin* value) {
    //@@preconditions
    assert(value != NULL);
    //@@end preconditions

    this->codonData.plugin = (dtkPlugin*)value;
}

//-------------------------------------------------------------------------
IPlugin* dtkPluginCodon::GetPlugin() {
    return this->codonData.plugin;
}

//-------------------------------------------------------------------------
void dtkPluginCodon::SetAttribute(const char* key, const char* value) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    assert(value != NULL);
    assert(strlen(value) >= 0);
    //@@end preconditions

    if (this->codonData.attributes == NULL) {
        this->codonData.attributes = new dtkHashTableStringOneKey(100);
    }

    StringIdRecType stringRec;
    strcpy(stringRec.inkey.id, key);    
    int slen = (int)strlen(value);
    stringRec.stuff = new char[slen+1];
    sprintf(stringRec.stuff, "%s", value);
    this->codonData.attributes->StringIdInsert(stringRec.inkey, &stringRec);
}

//-------------------------------------------------------------------------
const char* dtkPluginCodon::GetAttribute(const char* key) {
    //@@preconditions
    assert(key != NULL);
    assert(strlen(key) > 0);
    //@@end preconditions

    if (this->codonData.attributes == NULL) {
        return NULL;
    }
    StringIdRecType stringRec;
    strcpy(stringRec.inkey.id, key);
    if (STRID_STATUS_OK == this->codonData.attributes->StringIdFind(stringRec.inkey, & stringRec)) { 
        return stringRec.stuff;
    }
    return NULL;
}

//-------------------------------------------------------------------------
dtkPluginCodon::dtkPluginCodon() {
    memset(&this->codonData, 0, sizeof(_fbCodon_s));
}

//-------------------------------------------------------------------------
dtkPluginCodon::~dtkPluginCodon() {
    if (this->codonData.attributes != NULL) {
        delete this->codonData.attributes;
        this->codonData.attributes = NULL;
    }
    if (this->codonData.name != NULL) {
        delete[] this->codonData.name;
        this->codonData.name = NULL;
    }
    if (this->codonData.id != NULL) {
        delete[] this->codonData.id;
        this->codonData.id = NULL;
    }
    if (this->codonData.condition != NULL) {
        delete[] this->codonData.condition;
        this->codonData.condition = NULL;
    }
    if (this->codonData.xmlvalue) {
        delete[] this->codonData.xmlvalue;
        this->codonData.xmlvalue = 0;
    }
}
