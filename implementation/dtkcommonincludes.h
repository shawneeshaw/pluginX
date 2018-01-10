#ifndef DTKCOMMONINCLUDES_H
#define DTKCOMMONINCLUDES_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif

//standard system includes.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef MEMTRACK  //memory leak detection
#include "memman.h"
#endif

typedef char char256[256];

#include "dtkframeluascript/dtkluascriptframeincludes.h"
#include "dtkframeplugin/dtkpluginframeincludes.h"
#include "dtkframeplugintree/dtkplugintreeframeincludes.h"

#endif //DTKCOMMONINCLUDES_H

