#ifndef CPLINCLUDE_H
#define CPLINCLUDE_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif


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

//-----------------------------------------------------------------------------
//class includes.
//-----------------------------------------------------------------------------
//

//interfaces.
#include <iplugin.h>
#include <iplugincodon.h>
#include <iplugintreenode.h>
#include <iplugintreepath.h>
#include <iplugintree.h>
#include <iservice.h>

//simplecom object
#include <cplcom.h>

//zplugin api..
#include <cpluginlib.h>

//services
#include <service/caxservice.h>

#endif //CPLINCLUDE_H
