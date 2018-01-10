#include <cpl.h>
#include "caxservicestringparser.h"
#include "caxservicestringparserimp.h"

//-------------------------------------------------------------------------
// class caxServiceStringParserImp
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
caxServiceStringParserImp * caxServiceStringParserImp::New() {
    return new caxServiceStringParserImp;
}

//-------------------------------------------------------------------------
const char* caxServiceStringParserImp::Parse(const char* buff) {
    //@@preconditions
    assert(buff != NULL);
    //@@end preconditions

    printf("new parser -- overrided\n");
    return buff;
}
