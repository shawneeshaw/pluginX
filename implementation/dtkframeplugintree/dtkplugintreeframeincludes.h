#ifndef DTKPLUGINTREEFRAMEINCLUDES_H
#define DTKPLUGINTREEFRAMEINCLUDES_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#pragma warning( disable : 4800 ) // disable  unreferenced formal parameter
#endif

//-----------------------------------------------------------------------------
//precondition interface
//-----------------------------------------------------------------------------

class IPluginTreeNode;
class IPluginTreePath;
class IPluginTree;

//-----------------------------------------------------------------------------
//precondition class
//-----------------------------------------------------------------------------

class dtkPluginTree;
class dtkPluginTreeNode;
class dtkPluginTreePath;
class dtkPluginTreeMap;

//-----------------------------------------------------------------------------
//standard includes.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//dependency includes.
//-----------------------------------------------------------------------------

#include "../dtkframeplugin/dtkpluginframeincludes.h"

//-----------------------------------------------------------------------------
//class includes
//-----------------------------------------------------------------------------

#include <iplugintreenode.h>
#include <iplugintreepath.h>
#include <iplugintree.h>

#include "dtkplugintree.h"
#include "dtkplugintreenode.h"
#include "dtkplugintreepath.h"
#include "dtkplugintreemap.h"

#endif //DTKPLUGINTREEFRAMEINCLUDES_H
