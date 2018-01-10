#ifndef DTLUASCRIPTFRAMEINCLUDE_H
#define DTLUASCRIPTFRAMEINCLUDE_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif

//class definitions

//standard system includes.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef MEMTRACK  //memory leak detection
#include "memman.h"
#endif

//class includes.
#include "dtkluascript.h"
#include "dtkluascriptutility.h"
#include "dtkluamanager.h"
#include "dtkluascriptproxy.h"
#include "dtkluaproxy.h"

#endif //DTLUASCRIPTFRAMEINCLUDE_H
