#include <stdlib.h>
#include <assert.h>
#include <string>

//local include
#include <utest.h>
#include <utest_private.h>

//zplugin lib.
#include <cpl.h>

#include "../simpleservice/src/caxshape.h"
#include "../../services/stringparser/src/caxservicestringparser.h"

//-----------------------------------------------------------------------------
TEST(PluginTest_cpl_Test_1) {
    printf("PluginTest.., call simple lua file\n");

    const char* path = ".\\bin";

    //initialize 
    cpl_init();
    cpl_loadPlugins(path);

    //...
    cpl_luaRunScript("simple_call();");

    //shutdown cpl_
    cpl_deInit();

    printf("End...\n");
};

//-----------------------------------------------------------------------------
TEST(PluginTest_cpl_Test_2) {
    printf("PluginTest.., simple dll plugin\n");
    const char* path = ".\\bin";

    //initialize cpl_
    cpl_init();
    cpl_loadPlugins(path);

    caxShape* pShape = caxShape::New();
    assert(pShape != NULL);
    pShape->DrawSomething(); //should output draw circle.
    pShape->Release();

    //shutdown cpl_
    cpl_deInit();

    printf("End...\n");
};


//-----------------------------------------------------------------------------
TEST(PluginTest_cpl_Test_3) {
    printf("PluginTest.., simple dll service\n");
    const char* path = ".\\bin";

    //initialize cpl_
    cpl_init();
    cpl_loadPlugins(path);

    void* luaState = 0;
    cpl_luaGetVM(&luaState);

    cpl_initializeServicesSubsystem("/Workbench/Services");
    cpl_startAllServices();

    caxServiceStringParser* parser=NULL;
    cpl_findService("ServiceStringParser", (void**)&parser);
    assert(parser != NULL);
    parser->Parse("Hello world\n");

    cpl_unloadAllServices();

    //shutdown cpl_
    cpl_deInit();

    printf("End...\n");
};

//-----------------------------------------------------------------------------
TEST(PluginTest_cpl_Test_4) {
    printf("PluginTest.., data tplengine service\n");
    const char* path = ".\\bin";

    //initialize cpl_
    cpl_init();
    cpl_loadPlugins(path);

    cpl_initializeServicesSubsystem("/Workbench/Services");
    cpl_startAllServices();

    caxServiceStringParser* dataTPLEngine =NULL;
    cpl_findService("ServiceDataTPLEngine", (void**)&dataTPLEngine);
    assert(dataTPLEngine != NULL);

    cpl_luaRunScript("DataTPLEngine.DeformEDP()");

    //shutdown cpl_
    cpl_deInit();

    printf("End...\n");
};