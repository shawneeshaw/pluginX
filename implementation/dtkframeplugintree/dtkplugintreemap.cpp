#include "dtkplugintreeframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginTreeMap);

//-----------------------------------------------------------------------------
// class dtkPluginTreeMap
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int dtkPluginTreeMap::DoInitialization() {
    return 1;
}

//-----------------------------------------------------------------------------
int dtkPluginTreeMap::DoCleanup() {
    return 1;
}

//-----------------------------------------------------------------------------
dtkPluginTreePath* dtkPluginTreeMap::CreatePath(const char* path_name) {
    //@@preconditions
    assert(path_name != NULL);
    assert(path_name[0] != '\0');
    //@@end preconditions

    if (this->rootPath == NULL) {
        this->rootPath = dtkPluginTreePath::New();
        this->rootPath->Allocate(10, 10);
    }
    return this->CreatePath(this->rootPath, path_name);
}

//-----------------------------------------------------------------------------
static char* Join(char** split_str, int num, char separator) {
    static char text[1024];
    for (int i = 0; i < num; i++) {
        (i == 0) ? sprintf(text, "%s",split_str[i]) : sprintf(text, "%s%s", text, split_str[i]);
        sprintf(text, "%s/", text);
    }
    int len = strlen(text);
    text[len-1] = '\0';
    return text;
}

//-----------------------------------------------------------------------------
dtkPluginTreePath* dtkPluginTreeMap::CreatePath(dtkPluginTreePath* path, const char* path_name) {
    //@@preconditions
    assert(path_name != NULL);
    assert(path_name[0] != '\0');
    assert(path != NULL);
    //@@end preconditions

    int num = 0;
    char** split_str = NULL, separator = '/'; 
    dtkSystemTools::Split(path_name, split_str, num, separator);

    int i = 0;
    dtkPluginTreePath* curPath = path;
	while (i < num) {
        dtkPluginTreeNode* nextPath = curPath->GetItemA(split_str[i]);
		if (nextPath == NULL) {
            nextPath = dtkPluginTreePath::New();
            nextPath->SetName(split_str[i]);
            nextPath->SetPath(Join(split_str, i+1, separator));
            curPath->InsertNextItem(nextPath);
		}
		curPath = (dtkPluginTreePath*)nextPath;
		++i;
	}
            
    for (int j = 0; j < num; j++) {
        delete[] split_str[j];
    }
    delete[] split_str;
    return curPath;
}

//-----------------------------------------------------------------------------
dtkPluginTreePath* dtkPluginTreeMap::GetPath(const char* path_name) {
    //@@preconditions
    assert(path_name != NULL);
    assert(path_name[0] != '\0');
    //@@end preconditions

    if (this->rootPath == NULL) {
        return NULL;
    }
    
    int num = 0;
    char** split_str = NULL, separator = '/'; 
    dtkSystemTools::Split(path_name, split_str, num, separator);

    int i = 0, find = 1;
    dtkPluginTreePath* curPath = this->rootPath;
	while (i < num) {
        dtkPluginTreeNode* nextPath = curPath->GetItemA(split_str[i]);
		if (nextPath == NULL) {
            find = 0;
            break;
		}
		curPath = (dtkPluginTreePath*)nextPath;
		++i;
	}
            
    for (int j = 0; j < num; j++) {
        delete[] split_str[j];
    }
    delete[] split_str;

    return find == 1 ? curPath : NULL;
}

//-----------------------------------------------------------------------------
dtkPluginTreeMap::dtkPluginTreeMap() {
    this->rootPath = 0;
}

//-----------------------------------------------------------------------------
dtkPluginTreeMap::~dtkPluginTreeMap() {
    if (this->rootPath != NULL) {
        this->rootPath->Release();
    }
}
