#include <cpl.h>
#include "caxservicedatatplengine.h"
#include "caxservicedatatplengineimp.h"
#include <datatplengine.h>

//-------------------------------------------------------------------------
// class caxServiceDataTPLEngineImp
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
caxServiceDataTPLEngineImp * caxServiceDataTPLEngineImp::New() {
    return new caxServiceDataTPLEngineImp;
}

//-------------------------------------------------------------------------
void caxServiceDataTPLEngineImp::InitializeService() {
    caxService::InitializeService();

    void* luaState = NULL;
    cpl_luaGetVM(&luaState);
    assert(luaState != NULL);

    IPluginTree* pluginTree = NULL;
    cpl_getPluginTree(&pluginTree);
    assert(pluginTree != NULL);

    DataTPLEngineLoad(luaState);    

    this->RegisterApp(pluginTree, "/Workbench/Tools");
    //DataTPLEngineRegisterAppProgram("EDP", "E:/dir_work/pilot/proj/layer3/post/bin/Debug/postworkbench.exe");
}

//-------------------------------------------------------------------------
void caxServiceDataTPLEngineImp::UnloadService() {
    DataTPLEngineUnLoad();

    caxService::UnloadService();
}

//-----------------------------------------------------------------------------
void caxServiceDataTPLEngineImp::RegisterApp(IPluginTree* pluginTree, const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) > 0);
    //@@end preconditions

    IPluginTreePath* treepath = pluginTree->GetTreePath(path);
    if (treepath == NULL) {
        return;
    }
    int numItem = treepath->GetNumberOfItems();
    for (int i = 0; i < numItem; i++) {
        IPluginTreeNode* node = treepath->GetItem(i);
        if (node->IsComposite()) {
            const char* path = node->GetPath();
            assert(path != NULL);           
            this->RegisterApp(pluginTree, path);
        }
        else {
            IPluginCodon* codon = node->GetCodon();
            assert(codon != NULL);
            const char* name = codon->GetName();
            if (strcmp(name, "APP") == 0) {
                const char* id = codon->GetId();
                assert(id != NULL);
                const char* path = codon->GetAttribute("path");
                assert(path != NULL);
                //verify application
                DataTPLEngineRegisterAppProgram((char*)id, (char*)path);
            }
        }
    }
}
