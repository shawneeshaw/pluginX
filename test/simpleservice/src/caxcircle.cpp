#include <cpl.h>
#include "caxshape.h"
#include "caxcircle.h"

//-------------------------------------------------------------------------
// class caxCircle
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
caxCircle * caxCircle::New() {
    return new caxCircle;
}

//-------------------------------------------------------------------------
void caxCircle::DrawSomething() {
    //@@preconditions
    //@@end preconditions

    printf("draw circle\n");
}
