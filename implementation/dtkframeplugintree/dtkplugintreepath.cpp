#include "dtkplugintreeframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginTreePath);


//-----------------------------------------------------------------------------
// class dtkPluginTreePath
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
dtkPluginTreePath::dtkPluginTreePath() : dtkPluginTreeNode(NULL) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
dtkPluginTreePath::dtkPluginTreePath(dtkPluginTreePath * pNode) : dtkPluginTreeNode(pNode)  {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
dtkPluginTreePath::~dtkPluginTreePath() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].Item != NULL) {
                this->Array[i].Item->Release();
                this->Array[i].Item = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}

//-----------------------------------------------------------------------------
int dtkPluginTreePath::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].Item != NULL) {
                    this->Array[i].Item->Release();
                    this->Array[i].Item = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbNodetem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].Item = NULL;
             this->Array[i].resourceId = 0;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-----------------------------------------------------------------------------
int dtkPluginTreePath::InsertNextItem(IPluginTreeNode* node) {    
    //@@preconditons
    assert(node != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, (dtkPluginTreeNode*)node);
    return this->MaxId;
}

//-----------------------------------------------------------------------------
int dtkPluginTreePath::RemoveItem(IPluginTreeNode* node) {
    //@@preconditions
    assert(node != NULL);
    //@@end preconditions

    int id = -1;
    for (int i = 0; i <= this->MaxId; i++) {
        if (this->Array[i].Item == node) {
            id = i;
            break;
        }
    }
    assert(id != -1);

    //exchange position between lnId and MaxId, note: widget is not delete.
    if (id != this->MaxId) {
        this->Array[id] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-----------------------------------------------------------------------------
int dtkPluginTreePath::RemoveAllItems(){
    for (int i = 0; i <= this->MaxId; i++) {
        if (this->Array[i].Item != NULL) {
            this->Array[i].Item->Release();
            this->Array[i].Item = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}

//-----------------------------------------------------------------------------
void dtkPluginTreePath::InsertItem(int pos, dtkPluginTreeNode* node) {
    //@@preconditions
    assert(pos >= 0);
    assert(node != NULL);
    //@@end preconditions

    _fbNodetem_s * nodes;
    if (pos >= this->Size) {
        this->Reallocate(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    nodes = this->Array + pos;
    assert(nodes != NULL);

    nodes->Item = node;
    nodes->resourceId = 0;

    //set as parent.
    nodes->Item->SetParent(this);
}
 
//-----------------------------------------------------------------------------
dtkPluginTreePath::_fbNodetem_s* dtkPluginTreePath::Reallocate(int sz) {
    //@@preconditions
    assert(sz > 0);
    //@@end preconditions

    int newSize = 0;
    if (sz >= this->Size) {
        newSize = this->Size + sz;
    }
    else {
        assert(0);
        newSize = sz;
    }

    dtkPluginTreePath::_fbNodetem_s * newArray = new dtkPluginTreePath::_fbNodetem_s[newSize];

    for (int j = 0; j < newSize; j++) {
        newArray[j].Item = NULL;
        newArray[j].resourceId = 0;
    }

    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].Item = this->Array[i].Item;
        newArray[i].resourceId = this->Array[i].resourceId;
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-----------------------------------------------------------------------------
int dtkPluginTreePath::GetNumberOfNestItems() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItem(this);
}

//-----------------------------------------------------------------------------
int dtkPluginTreePath::GetNestSubItem(dtkPluginTreePath* path) {
    //@@preconditions
    assert(path != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = path->GetNumberOfNestItems();
    for (int i = 0; i < numItem ; i++) {
        dtkPluginTreeNode* node = path->GetItemA(i);
        if (node->IsComposite() == 1) {
            count += this->GetNestSubItem((dtkPluginTreePath*)node);
        }
        else {
            count++;
        }        
    }
    return count;
}

//-----------------------------------------------------------------------------
IPluginTreeNode* dtkPluginTreePath::GetItem(char* subID) {
    //@@preconditions
    assert(subID != NULL);
    //@@end preconditions

    for (int i = 0; i <= this->MaxId; i++) {
        const char* name = this->Array[i].Item->GetName();
        if (strcmp(subID, name) == 0) {
            return this->Array[i].Item;
        }
    }
    return NULL;    
}

//-----------------------------------------------------------------------------
IPluginTreeNode* dtkPluginTreePath::GetItem(IPluginCodon* subID) {
    //@@preconditions
    assert(subID != NULL);
    //@@end preconditions

    for (int i = 0; i <= this->MaxId; i++) {
        if (this->Array[i].Item->GetCodon() == subID) { 
            return this->Array[i].Item;
        }
    }
    return NULL;    
}

//-------------------------------------------------------------------------
dtkPluginTreeNode* dtkPluginTreePath::GetItemA(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfItems());
    assert(this->Array != NULL);
    //@@end preconditons
    
    return this->Array[pos].Item;    
}

//-----------------------------------------------------------------------------
dtkPluginTreeNode* dtkPluginTreePath::GetItemA(char* subID) {
    //@@preconditions
    assert(subID != NULL);
    //@@end preconditions

    for (int i = 0; i <= this->MaxId; i++) {
        const char* name = this->Array[i].Item->GetName();
        if (strcmp(subID, name) == 0) {
            return this->Array[i].Item;
        }
    }
    return NULL;    
}

//-----------------------------------------------------------------------------
void dtkPluginTreePath::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    dtkPluginTreeNode::SetName(name);
}

//-----------------------------------------------------------------------------
const char* dtkPluginTreePath::GetName() {
    return  dtkPluginTreeNode::GetName();
}

//-----------------------------------------------------------------------------
void dtkPluginTreePath::SetPath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) >= 0);
    //@@end preconditions

    dtkPluginTreeNode::SetPath(path);
}

//-----------------------------------------------------------------------------
const char* dtkPluginTreePath::GetPath() {
    return  dtkPluginTreeNode::GetPath();
}

//-----------------------------------------------------------------------------
void dtkPluginTreePath::SetUserData(const void* usrData) {
    //@@preconditions
    //@@end preconditions

    dtkPluginTreeNode::SetUserData(usrData);
}

//-----------------------------------------------------------------------------
const void* dtkPluginTreePath::GetUserData() {
    return  dtkPluginTreeNode::GetUserData();
}

//-----------------------------------------------------------------------------
void dtkPluginTreePath::SetCodon(IPluginCodon* codon) {
    //@@preconditions
    assert(codon != NULL);
    //@@end preconditions

    dtkPluginTreeNode::SetCodon(codon);
}

//-----------------------------------------------------------------------------
IPluginCodon* dtkPluginTreePath::GetCodon() {
    return dtkPluginTreeNode::GetCodon();
}

//-----------------------------------------------------------------------------
void dtkPluginTreePath::SetParent(IPluginTreePath* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    dtkPluginTreeNode::SetParent(parent);
}
   
//-----------------------------------------------------------------------------
IPluginTreePath* dtkPluginTreePath::GetParent() {
    return dtkPluginTreeNode::GetParent();
}
