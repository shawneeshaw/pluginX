#include "dtkframeobjectincludes.h"
#include <sys/stat.h>

//-----------------------------------------------------------------------------
dtkDirectory* dtkDirectory::New() {
    return new dtkDirectory;
}

//-----------------------------------------------------------------------------
dtkDirectory::dtkDirectory() : Path(0), Files(0), NumberOfFiles(0) {
}

//-----------------------------------------------------------------------------
dtkDirectory::~dtkDirectory() {
    this->CleanUpFilesAndPath();
}

//-----------------------------------------------------------------------------
void dtkDirectory::CleanUpFilesAndPath() {
    for (int i =0; i < this->NumberOfFiles; i++) {
        delete [] this->Files[i];
    }
    delete [] this->Files;
    delete [] this->Path;
    this->Files = 0;
    this->Path = 0;
    this->NumberOfFiles = 0;
}

// First microsoft and borland compilers
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#include "windows.h"
#include <io.h>
#include <ctype.h>
#include <direct.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//-----------------------------------------------------------------------------
int dtkDirectory::Open(const char* name) {
    // clean up from any previous open
    this->CleanUpFilesAndPath();
    char* buf=0;
    int n = static_cast<int>(strlen(name));
    if (name[n - 1] == '/') {
        buf = new char[n + 1 + 1];
        sprintf(buf, "%s*", name);
    } 
    else {
        buf = new char[n + 2 + 1];
        sprintf(buf, "%s/*", name);
    }
    struct _finddata_t data;      // data of current file
    
    // First count the number of files in the directory
#if _MSC_VER < 1300
    long srchHandle;
#else
    intptr_t srchHandle;
#endif
    srchHandle = _findfirst(buf, &data);
    if (srchHandle == -1) {
        this->NumberOfFiles = 0;
        _findclose(srchHandle);
        delete[] buf;
        return 0;
    }   
    this->NumberOfFiles = 1;  
    while(_findnext(srchHandle, &data) != -1) {
        this->NumberOfFiles++;
    }
    this->Files = new char*[this->NumberOfFiles];
    // close the handle 
    _findclose(srchHandle);
    // Now put them into the file array
    srchHandle = _findfirst(buf, &data);
    delete [] buf;
  
    if (srchHandle == -1) {
        this->NumberOfFiles = 0;
        _findclose(srchHandle);
        return 0;
    }
  
    // Loop through names
    int i = 0;
    do {
        this->Files[i] = strcpy(new char[strlen(data.name)+1], data.name);
        i++;
    } 
    while (_findnext(srchHandle, &data) != -1);
    this->Path = strcpy(new char[strlen(name)+1], name);
    return _findclose(srchHandle) != -1;
}

//-----------------------------------------------------------------------------
const char* dtkDirectory::GetCurrentWorkingDirectory(char* buf, unsigned int len) {
    return _getcwd(buf, len);
}

#else

// Now the POSIX style directory access
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

//-----------------------------------------------------------------------------
int dtkDirectory::Open(const char* name) {
    // clean up from any previous open
    this->CleanUpFilesAndPath();

    DIR* dir = opendir(name);
    if (!dir) {
        return 0;
    }
    this->NumberOfFiles = 0;
    dirent* d =0;

    for (d = readdir(dir); d; d = readdir(dir)) {
        this->NumberOfFiles++;
    }
    this->Files = new char*[this->NumberOfFiles];
    closedir(dir);

    dir = opendir(name);
    if (!dir) {
        return 0;
    }
    int i = 0;
    for (d = readdir(dir); d; d = readdir(dir)) {
        this->Files[i] = strcpy(new char[strlen(d->d_name)+1], d->d_name);
        i++;
    }
    this->Path = strcpy(new char[strlen(name)+1], name);
    closedir(dir);
    return 1;
}

//-----------------------------------------------------------------------------
const char* dtkDirectory::GetCurrentWorkingDirectory(char* buf, unsigned int len) {
    return getcwd(buf, len);
}
#endif

//-----------------------------------------------------------------------------
const char* dtkDirectory::GetFile(int index) {
    if(index >= this->NumberOfFiles || index < 0) {
        assert(0);
        return 0;
    }  
    return this->Files[index];
}

//-----------------------------------------------------------------------------
int dtkDirectory::FileIsDirectory(const char * name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) > 0);
    //@@end preconditions

    struct stat fs;
    if (stat(name, & fs) == 0) {
#if _WIN32
        return ((fs.st_mode & _S_IFDIR) != 0);
#else
        return S_ISDIR(fs.st_mode);
#endif
    }
    else {
        return 0;
    }
}
