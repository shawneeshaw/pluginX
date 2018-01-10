#include <stdlib.h>
#include <assert.h>
#include <string>
#include <cpl.h>

//simple service..
#include "caxservicesayhello.h"
#include "caxsimpleobject.h"

//extern implement proxy.
extern "C" ImplementationProxy* SimpleObjectGetImplementationProxy(int & aTableCount);

void main() {
    //start application..
    cpl_init();

    //load plugins
    cpl_loadPlugins("./bin/plugins");

    //add user-defined class load tables.
    cpl_addClassLoadFunction(SimpleObjectGetImplementationProxy);

    //load class override info.
    cpl_loadClassOverrideInfo("/workspace/classoverride");

    //initialize servces.
    cpl_initializeServicesSubsystem("/workspace/services");

    //add user-defined services..
    cpl_addService("ServiceSayHello", caxServiceStringSayHello::New());
    
    //start services.
    cpl_startAllServices();

    //create simple object.
    caxSimpleObject* simpleMe = NULL;
    cpl_createObject("caxSimpleObject", (void**)&simpleMe, 1);
    assert(simpleMe != NULL);
    simpleMe->ShowMe();
    simpleMe->Release();

    //another implement method.
    caxSimpleObject* simpleMeTwo = caxSimpleObject::New();
    assert(simpleMeTwo != NULL);
    simpleMeTwo->ShowMe();
    simpleMeTwo->Release();
    
    //call service.
    caxServiceStringSayHello* sayHello = NULL;
    cpl_findService("ServiceSayHello", (void**)&sayHello);
    assert(sayHello != NULL);
    sayHello->Parse("Give me a feedback");

    //do something..
    cpl_luaRunScript("print(\"Say bye!\");");

    //unload services.
    cpl_unloadAllServices();

    //shutdown application..
    cpl_deInit();
}
