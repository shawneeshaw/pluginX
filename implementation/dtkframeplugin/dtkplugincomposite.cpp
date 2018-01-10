#include "dtkpluginframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkCompositePlugin);

//-------------------------------------------------------------------------
// class dtkCompositePlugin
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
dtkCompositePlugin::dtkCompositePlugin() : dtkPlugin(NULL) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-------------------------------------------------------------------------
dtkCompositePlugin::dtkCompositePlugin(dtkCompositePlugin * parent) : dtkPlugin(parent)  {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-------------------------------------------------------------------------
dtkCompositePlugin::~dtkCompositePlugin() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].PluginItem != NULL) {
                this->Array[i].PluginItem->Release();
                this->Array[i].PluginItem = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].PluginItem != NULL) {
                    this->Array[i].PluginItem->Release();
                    this->Array[i].PluginItem = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbPluginItem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].PluginItem = NULL;
             this->Array[i].resourceId = 0;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::InsertNextItem(dtkPlugin* plugin) {    
    //@@preconditons
    assert(plugin != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, plugin);
    return this->MaxId;
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::RemoveItem(dtkPlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int PluginId = -1;
    for (int i = 0; i < this->MaxId; i++) {
        if (this->Array[i].PluginItem == plugin) {
            PluginId = i;
            break;
        }
    }
    assert(PluginId != -1);

    //exchange position between lnId and MaxId, note: widget is not delete.
    if (PluginId != this->MaxId) {
        this->Array[PluginId] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int dtkCompositePlugin::RemoveAllItems(){
    for (int i = 0; i < this->MaxId; i++) {
        if (this->Array[i].PluginItem != NULL) {
            this->Array[i].PluginItem->Release();
            this->Array[i].PluginItem = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}

//-------------------------------------------------------------------------
void dtkCompositePlugin::InsertItem(int pos, dtkPlugin* plugin) {
    //@@preconditions
    assert(pos >= 0);
    assert(plugin != NULL);
    //@@end preconditions

    _fbPluginItem_s * plugins;
    if (pos >= this->Size) {
        this->Reallocate(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    plugins = this->Array + pos;
    assert(plugins != NULL);

    plugins->PluginItem = plugin;
    plugins->resourceId = 0;

    //set as parent.
    plugins->PluginItem->SetParent(this);
    return;
}
 
//-------------------------------------------------------------------------
dtkCompositePlugin::_fbPluginItem_s* dtkCompositePlugin::Reallocate(int sz) {
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

    dtkCompositePlugin::_fbPluginItem_s * newArray = new dtkCompositePlugin::_fbPluginItem_s[newSize];
    for (int j = 0; j < newSize; j++) {
        newArray[j].PluginItem = NULL;
        newArray[j].resourceId = 0;
    }

    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].PluginItem = this->Array[i].PluginItem;
        newArray[i].resourceId = this->Array[i].resourceId;
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNumberOfNestPlugins() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItem(this);
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNumberOfNestPluginsRequireLib() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItemRequireLib(this);
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNumberOfNestPluginsDLL() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItemDLL(this);
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNumberOfNestPluginsZScript() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItemZScript(this);
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNestSubItem(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);

        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItem((dtkCompositePlugin*)sub_plugin);
        }
        else {
            count++;
        }        
    }
    return count;
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNestSubItemRequireLib(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);

        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItemRequireLib((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkStringCollection* collection = sub_plugin->GetRequireLibs();
            if (collection != NULL) {                
                count += collection->GetNumberOfItem();
            }
        }        
    }
    return count;
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNestSubItemDLL(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItemDLL((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkStringCollection* collection = sub_plugin->GetDynamicFactories();
            if (collection != NULL) {                
                count += collection->GetNumberOfItem();
            }
        }        
    }
    return count;
}

//-------------------------------------------------------------------------
int dtkCompositePlugin::GetNestSubItemZScript(dtkCompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        dtkPlugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);

        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItemZScript((dtkCompositePlugin*)sub_plugin);
        }
        else {
            dtkStringCollection* collection = sub_plugin->GetZScriptLibs();
            if (collection != NULL) {                
                count += collection->GetNumberOfItem();
            }
        }        
    }
    return count;
}
