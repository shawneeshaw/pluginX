#include "dtkpluginframeincludes.h"

//@@standard macro.
DTKStandardNewCommandMacro(dtkPluginManager);

//-----------------------------------------------------------------------------
// class dtkPluginManager
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int dtkPluginManager::DoInitialization() {
    return 1;
}

//-----------------------------------------------------------------------------
int dtkPluginManager::DoCleanup() {
    return 1;
}

//-----------------------------------------------------------------------------
int dtkPluginManager::Parse(const char* path) {
    //@@precondition
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(this->rootPluginPath == NULL);
    //@@end preconditions

    char _path[2048]= {0};
    sprintf(_path, "%s", path);
    dtkSystemTools::ConvertWindowsPathToUnix(_path);
    assert(strlen(_path) > 0);

    this->rootPluginPath = dtkCompositePlugin::New();
    this->rootPluginPath->Allocate(10, 10);
    this->rootPluginPath->SetXmlName(_path);
    this->rootPluginPath->SetName(_path);

    return this->ParseInPath(this->rootPluginPath, _path);
}

//-----------------------------------------------------------------------------
int dtkPluginManager::ParseInPath(dtkCompositePlugin* plugins, const char* path) {
    //@@precondition
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(plugins != NULL);
    //@@end preconditions

    dtkDirectory* dir = dtkDirectory::New();
    if (!dir->Open(path)) {
         dir->Release();
         return 0;
    }      
    
    int ret = 0;
    for (int i = 0; i < dir->GetNumberOfFiles(); i++) {
        const char* name = dir->GetFile(i);
        assert(name != NULL);
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0){
            continue;
        }
        char fullname[2048];
        sprintf(fullname, "%s/%s", path, name);
        if (dtkDirectory::FileIsDirectory(fullname)) {
            dtkCompositePlugin* newPath = dtkCompositePlugin::New();
            newPath->Allocate(10, 10);
            newPath->SetName(fullname);
            if (this->ParseInPath(newPath, fullname)) {
                plugins->InsertNextItem(newPath);
                newPath->SetParent(plugins);
                ret = 1;
            }
            else {
                newPath->Release();
            }
            continue;
        }       
        if (this->ParsePlugin(plugins, fullname)) {
            ret = 1;
        }
    }
    dir->Release();
    return ret;
}

//-----------------------------------------------------------------------------
static int NameIsPluginFileName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) > 0);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    char* ret = strstr(copy, ".plugin");
    if   (ret != NULL) {
        if (strlen(ret) == strlen(".plugin")) {
            delete [] copy;
            return 1;
        }
    }
    delete [] copy;
    return 0;
}

//-----------------------------------------------------------------------------
int dtkPluginManager::ParsePlugin(dtkCompositePlugin* plugins, const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    assert(strlen(fname) > 0);
    assert(plugins != NULL);
    //@@end preconditions

    if (NameIsPluginFileName(fname) == 0) {
        return 0;        
    }
    dtkPlugin* plugin = new dtkPlugin;
    assert(plugin != NULL);

    dtkPluginXmlReader* reader = dtkPluginXmlReader::New();
    assert(reader != NULL);

    plugin->SetXmlName(fname);
    reader->SetPlugin(plugin);
    reader->SetXmlSource(fname);

    int ret = reader->Parse();    
    if (ret == 1) {
        plugins->InsertNextItem(plugin);
    }
    else {
        plugin->Release();
    }
    reader->Release();
    return ret;
}

//-----------------------------------------------------------------------------
dtkCompositePlugin* dtkPluginManager::GetRootPath() {
    return this->rootPluginPath;
}

//-----------------------------------------------------------------------------
dtkPluginManager::dtkPluginManager() {
    this->rootPluginPath = 0;
}

//-----------------------------------------------------------------------------
dtkPluginManager::~dtkPluginManager() {
    if (this->rootPluginPath != NULL) {
        this->rootPluginPath->Release();
    }
}
