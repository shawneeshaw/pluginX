#ifndef DTKFRAMEWORKINCLUDE_H
#define DTKFRAMEWORKINCLUDE_H

/* first include the local configuration for this machine */
#define __DTK_SYSTEM_INCLUDES__INSIDE
#include "dtkwin32header.h"
#undef  __DTK_SYSTEM_INCLUDES__INSIDE

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif


//
//----macro to implement the standard form of the New() method
//
#define DTKStandardNewCommandMacro(thisClass) \
  thisClass* thisClass::New() \
  { \
    dtkObject* ret = dtkObjectFactory::CreateInstance(#thisClass); \
    if(ret) \
      { \
      return static_cast<thisClass*>(ret); \
      } \
    return new thisClass; \
  }

#define DTK_CREATE_CREATE_FUNCTION(classname) \
  static dtkObject* dtkObjectFactoryCreate##classname() \
  { \
     return classname::New(); \
  }

//-----------------------------------------------------------------------------
//class predefinitions.
//-----------------------------------------------------------------------------
//
class dtkTimeStamp;
class dtkObjectBase;
class dtkObject;
class dtkObjectFactory;
class dtkObjectFactoryPool;
class dtkDirectory;
class dtkDynamicLoader;
class dtkCriticalSection;

//-----------------------------------------------------------------------------
//standard definitions.
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef MEMTRACK  //memory leak detection
#include "memman.h"
#endif

//-------------------------------------------------------------------------
typedef struct _DGUID {
    int   Data1;
    short Data2;
    short Data3;
    char  Data4[8];
} DGUID;

#define REFDGUID const DGUID&

//-------------------------------------------------------------------------
typedef void* (*CREATE_FUNC)();

//-------------------------------------------------------------------------
typedef struct _ImplementationProxy {
    char progId[64];
    DGUID classId;
    CREATE_FUNC func;
} 
ImplementationProxy;

//-------------------------------------------------------------------------
inline BOOL IsEqualDGUID(REFDGUID r1, REFDGUID r2) 
{ return !memcmp(&r1, &r2, sizeof(DGUID)); }

inline BOOL operator == (REFDGUID r1, REFDGUID r2) 
{ return !memcmp(&r1, &r2, sizeof(DGUID)); }

inline BOOL operator != (REFDGUID r1, REFDGUID r2) 
{ return !(r1 == r2); }

typedef ImplementationProxy* (*IMPLEMENTPROXY_FUNC)(int&);

//-----------------------------------------------------------------------------
//class includes.
//-----------------------------------------------------------------------------
//
#include <iservice.h>

typedef ImplementationProxy dtkImplementationProxy;

#include "dtktimestamp.h"
#include "dtkobjectbase.h"
#include "dtkobject.h"
#include "dtkcriticalsection.h"
#include "dtkobjectfactory.h"
#include "dtkobjectfactorypool.h"
#include "dtksystemtools.h"
#include "dtkdirectory.h"
#include "dtkdynamicloader.h"
#include "dtkstring.h"
#include "dtkstringcollection.h"
#include "dtkhashtablestring.h"
#include "dtkhashtableobject.h"
#include "dtkcreator.h"
#include "dtkimplementionproxycollection.h"
#include "dtkservice.h"
#include "dtkservicecollection.h"
#include "dtkservicemanager.h"
#include "dtksort.h"

#endif //DTKFRAMEWORKINCLUDE_H
