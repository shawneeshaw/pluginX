#include "dtkplugintreeframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginTreeNode);

//-----------------------------------------------------------------------------
// class dtkPluginTreeNode
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
void dtkPluginTreeNode::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    if (this->nodeData.name != NULL) {
        delete[] this->nodeData.name;
        this->nodeData.name = NULL;
    }
    int slen = (int)strlen(name);
    this->nodeData.name = new char[slen+1];
    strcpy(this->nodeData.name, name);
}

//-----------------------------------------------------------------------------
const char* dtkPluginTreeNode::GetName() {
    return this->nodeData.name;
}

//-----------------------------------------------------------------------------
void dtkPluginTreeNode::SetPath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) >= 0);
    //@@end preconditions

    if (this->nodeData.path != NULL) {
        delete[] this->nodeData.path;
        this->nodeData.path = NULL;
    }
    int slen = (int)strlen(path);
    this->nodeData.path = new char[slen+1];
    strcpy(this->nodeData.path, path);
}

//-----------------------------------------------------------------------------
const char* dtkPluginTreeNode::GetPath() {
    return this->nodeData.path;
}

//-----------------------------------------------------------------------------
void dtkPluginTreeNode::SetUserData(const void* usrData) {
    this->nodeData.data = (void*)usrData;
}

//-----------------------------------------------------------------------------
const void* dtkPluginTreeNode::GetUserData() {
    return this->nodeData.data;
}

//-----------------------------------------------------------------------------
void dtkPluginTreeNode::SetCodon(IPluginCodon* codon) {
    //@@preconditions
    assert(codon != NULL);
    //@@end preconditions

    this->nodeData.codon = (dtkPluginCodon*)codon;
}

//-----------------------------------------------------------------------------
IPluginCodon* dtkPluginTreeNode::GetCodon() {
    return this->nodeData.codon;
}

//-----------------------------------------------------------------------------
void dtkPluginTreeNode::SetParent(IPluginTreePath* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    this->nodeData.parent = (dtkPluginTreePath*)parent;
}
   
//-----------------------------------------------------------------------------
 IPluginTreePath* dtkPluginTreeNode::GetParent() {
    return this->nodeData.parent;
}

 //-----------------------------------------------------------------------------
dtkPluginTreeNode::dtkPluginTreeNode() {
    memset(&this->nodeData, 0, sizeof(_fbNode_s));
    this->SetName("");
    this->SetPath("");
}

//-----------------------------------------------------------------------------
dtkPluginTreeNode::dtkPluginTreeNode(dtkPluginTreePath* parent) {
    memset(&this->nodeData, 0, sizeof(_fbNode_s));
    this->nodeData.parent = parent;
    this->SetName("");
    this->SetPath("");
}

//-----------------------------------------------------------------------------
dtkPluginTreeNode::~dtkPluginTreeNode() {
    if (this->nodeData.name != NULL) {
        delete[] this->nodeData.name;
        this->nodeData.name = NULL;
    }
    if (this->nodeData.path != NULL) {
        delete[] this->nodeData.path;
        this->nodeData.path = NULL;
    }
}
