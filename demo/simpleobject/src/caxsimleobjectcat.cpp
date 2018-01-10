#include <cpl.h>
#include "../../src/caxsimpleobject.h"
#include "caxsimleobjectcat.h"

//-------------------------------------------------------------------------
caxSimpleObjectCat * caxSimpleObjectCat::New() {
    return new caxSimpleObjectCat;
}

//-------------------------------------------------------------------------
void caxSimpleObjectCat::ShowMe() {
    printf("it is me! Miao, Miao ^-^ !\n");
}

//-------------------------------------------------------------------------
static ImplementationProxy ImplementationTable[] = {
    {"caxSimpleObjectCat", {0x3c561ae4, 0x912, 0x43bb, { 0x8c, 0xf0, 0xaf, 0xb8, 0x8e, 0x79, 0x27, 0xbd }}, (CREATE_FUNC)caxSimpleObjectCat::New }
};

//-------------------------------------------------------------------------
extern "C" ImplementationProxy* CoGetImplementationProxy(int & aTableCount) {
    aTableCount = sizeof(ImplementationTable) / sizeof(ImplementationProxy);
    return ImplementationTable;
}
