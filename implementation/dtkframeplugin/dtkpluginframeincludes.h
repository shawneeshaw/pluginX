#ifndef DTKPLUGINFRAMEINCLUDES_H
#define DTKPLUGINFRAMEINCLUDES_H

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
//interface definitions
//----------------------------------------------------------------------------
class IPlugin;
class IPluginCodon;

//
//-----------------------------------------------------------------------------
//class definitions
//----------------------------------------------------------------------------

class dtkPlugin;
class dtkPluginCodon;
class dtkPluginCodonCollection;
class dtkPluginExtension;
class dtkPluginExtensionCollection;
class dtkCompositePlugin;
class dtkPluginXmlReader;
class dtkPluginManager;

//-----------------------------------------------------------------------------
//system includes
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//interface includes
//-----------------------------------------------------------------------------

#include <iplugin.h>
#include <iplugincodon.h>

//-----------------------------------------------------------------------------
//dependent package
//-----------------------------------------------------------------------------

#include "../dtkframeobject/dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
//class includes
//-----------------------------------------------------------------------------

#include "dtkplugin.h"
#include "dtkplugincodon.h"
#include "dtkplugincodoncollection.h"
#include "dtkpluginextension.h"
#include "dtkpluginextensioncollection.h"
#include "dtkplugincomposite.h"
#include "dtkpluginxmlreader.h"
#include "dtkpluginmanager.h"

#endif //DTKPLUGINFRAMEINCLUDES_H
