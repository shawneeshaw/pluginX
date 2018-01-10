#include <cpl.h>
#include "caxservicesayhello.h"

//-------------------------------------------------------------------------
// class caxServiceStringSayHello
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
caxServiceStringSayHello * caxServiceStringSayHello::New() {
    return new caxServiceStringSayHello;
}

//-------------------------------------------------------------------------
const char* caxServiceStringSayHello::Parse(const char* buff) {
    //@@preconditions
    assert(buff != NULL);
    //@@end preconditions

    printf("hello world\n");
    return buff;
}
