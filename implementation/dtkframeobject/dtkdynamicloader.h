#ifndef DTKDYNAMICLOADER_H
#define DTKDYNAMICLOADER_H

// They are different on several different OS's
#if defined(__hpux)
# include <dl.h> // Needed for special dynamic loading on hp
  typedef shl_t dtkLibHandle;
#elif defined(_WIN32)
  typedef void* dtkLibHandle;
#else
  typedef void* dtkLibHandle;
#endif

class dtkDynamicLoader : public dtkObject {
public:
    /** create instance. */
    static dtkDynamicLoader* New();

    /** load a dynamic library into the current process. */
    static dtkLibHandle OpenLibrary(const char*);
    
    /** attempt to detach a dynamic library from the process. */
    static int CloseLibrary(dtkLibHandle);

    /** find the address of the symbol in the given library */
    static void* GetSymbolAddress(dtkLibHandle, const char*);

    /** return the library prefix for the given architecture */
    static const char* LibPrefix();

    /** return the library extension for the given architecture */
    static const char* LibExtension();

    /** return the last error produced from a calls made on this class. */
    static const char* LastError();
  
protected:
    // constructor.
    dtkDynamicLoader();

    //destructor.
    virtual ~dtkDynamicLoader();    
};

#endif //DTKDYNAMICLOADER_H

