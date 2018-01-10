#include "dtkframeobjectincludes.h"

//----------------------------------------------------------------------------
dtkDynamicLoader* dtkDynamicLoader::New() {
    return new dtkDynamicLoader;
}

//-----------------------------------------------------------------------------
dtkDynamicLoader::dtkDynamicLoader() {
}

//-----------------------------------------------------------------------------
dtkDynamicLoader::~dtkDynamicLoader() {
}

// ---------------------------------------------------------------
// 1. Implementation for HPUX  machines
#ifdef __hpux
#define VTKDYNAMICLOADER_DEFINED 1
#include <dl.h>

//-----------------------------------------------------------------------------
dtkLibHandle dtkDynamicLoader::OpenLibrary(const char* libname ) {
    return shl_load(libname, BIND_DEFERRED | DYNAMIC_PATH, 0L);
}

//-----------------------------------------------------------------------------
int dtkDynamicLoader::CloseLibrary(dtkLibHandle lib) {
    return 0;
}

//-----------------------------------------------------------------------------
void* dtkDynamicLoader::GetSymbolAddress(dtkLibHandle lib, const char* sym) { 
    void* addr;
    int status;

    status = shl_findsym (&lib, sym, TYPE_PROCEDURE, &addr);
    return (status < 0) ? (void*)0 : addr;
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibPrefix() { 
    return "lib";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibExtension() {
    return ".sl";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LastError() {
    return 0;
}
#endif


// ---------------------------------------------------------------
// 2. Implementation for Darwin (including OSX) Machines

#ifdef __APPLE__
#define VTKDYNAMICLOADER_DEFINED

// Visual Age Compiler for Mac OSX does not understand this extension.
#if defined(__IBMCPP__) && !defined(__private_extern__)
# define __private_extern__
#endif

#include <mach-o/dyld.h>

//-----------------------------------------------------------------------------
dtkLibHandle dtkDynamicLoader::OpenLibrary(const char* libname ) {
    NSObjectFileImageReturnCode rc;
    NSObjectFileImage image;

    rc = NSCreateObjectFileImageFromFile(libname, &image);
    return NSLinkModule(image, libname, TRUE);
}

//-----------------------------------------------------------------------------
int dtkDynamicLoader::CloseLibrary(dtkLibHandle) {
    return 0;
}

//-----------------------------------------------------------------------------
void* dtkDynamicLoader::GetSymbolAddress(dtkLibHandle, const char* sym) {
    void *result = 0;
    // global 'C' symbols names are preceded with an underscore '_'
    char *_sym = new char[ strlen(sym) + 2 ];
    strcpy( _sym + 1, sym );
    _sym[0] = '_';
    if (NSIsSymbolNameDefined(_sym)) {
        NSSymbol symbol = NSLookupAndBindSymbol(_sym);
        if (symbol) {
            result = NSAddressOfSymbol(symbol);
        }
    }
    else {
    }

    delete[] _sym;
    return result;
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibPrefix() {
    return "lib";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibExtension() {
    return ".so";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LastError() {
    return 0;
}

#endif

// ---------------------------------------------------------------
// 3. Implementation for Windows win32 code
#ifdef _WIN32
# include "windows.h"
#define VTKDYNAMICLOADER_DEFINED 1

//-----------------------------------------------------------------------------
dtkLibHandle dtkDynamicLoader::OpenLibrary(const char* libname ) {
#ifdef UNICODE
    wchar_t *libn = new wchar_t [mbstowcs(NULL, libname, 32000)+1];
    mbstowcs(libn, libname, 32000);
    dtkLibHandle ret = LoadLibrary(libn);
    delete [] libn;
    return ret;
#else
    return LoadLibrary(libname);
#endif
}

//-----------------------------------------------------------------------------
int dtkDynamicLoader::CloseLibrary(dtkLibHandle lib) {
    return (int)FreeLibrary(static_cast<HMODULE>(lib));
}

//-----------------------------------------------------------------------------
void* dtkDynamicLoader::GetSymbolAddress(dtkLibHandle lib, const char* sym) { 
#if defined (UNICODE) && !defined(_MSC_VER)
    wchar_t *wsym = new wchar_t [mbstowcs(NULL, sym, 32000)+1];
    mbstowcs(wsym, sym, 32000);
    // Force GetProcAddress to return void* with a c style cast
    // This is because you can not cast a function to a void* without
    // an error on gcc 3.2 and ANSI C++, 
    void *ret = (void*)GetProcAddress(lib, wsym);
    delete [] wsym;
    return ret;
#else
    return (void*)GetProcAddress(static_cast<HMODULE>(lib), sym);
#endif
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibPrefix() { 
    return "";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibExtension() {
    return ".dll";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LastError() {
    LPVOID lpMsgBuf;
    FormatMessage( 
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL 
                );
  
    // Free the buffer.
    static char* str = 0;
    delete [] str;
    if (lpMsgBuf) {
        str = strcpy(new char[strlen((char*)lpMsgBuf)+1], (char*)lpMsgBuf);
        LocalFree( lpMsgBuf );
    }
    return str;
}
#endif

// ---------------------------------------------------------------
// 4. Implementation for default UNIX machines.
// if nothing has been defined then use this
#ifndef VTKDYNAMICLOADER_DEFINED
#define VTKDYNAMICLOADER_DEFINED
// Setup for most unix machines
#include <dlfcn.h>

//-----------------------------------------------------------------------------
dtkLibHandle dtkDynamicLoader::OpenLibrary(const char* libname ) {
    return dlopen(libname, RTLD_LAZY);
}

//-----------------------------------------------------------------------------
int dtkDynamicLoader::CloseLibrary(dtkLibHandle lib) {
    // dlclose returns 0 on success, and non-dtk on error.
    return !((int)dlclose(lib));
}

//-----------------------------------------------------------------------------
void* dtkDynamicLoader::GetSymbolAddress(dtkLibHandle lib, const char* sym) { 
    return dlsym(lib, sym);
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibPrefix() { 
    return "lib";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LibExtension() {
    return ".so";
}

//-----------------------------------------------------------------------------
const char* dtkDynamicLoader::LastError() {
    return dlerror(); 
}

#endif
