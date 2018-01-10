#include <cpl.h>
#include "caxsimpleobject.h"

//-------------------------------------------------------------------------
// class caxSimpleObjectImp
//-------------------------------------------------------------------------
//
class caxSimpleObjectImp : public caxSimpleObject {
public:
    /** create instance */
    static caxSimpleObjectImp * New();

public:
    /** show me.*/
    virtual void ShowMe();

protected:    
    //constructor
    caxSimpleObjectImp() {}

    //destructor.
    virtual ~caxSimpleObjectImp() {}
};

//-------------------------------------------------------------------------
caxSimpleObjectImp * caxSimpleObjectImp::New() {
    return new caxSimpleObjectImp;
}

//-------------------------------------------------------------------------
void caxSimpleObjectImp::ShowMe() {
    printf("it is me! simple object\n");
}

//-------------------------------------------------------------------------
static ImplementationProxy ImplementationTable[] = {
    {"caxSimpleObject", {0x3c561ae4, 0x912, 0x43bb, { 0x8c, 0xf0, 0xaf, 0xb8, 0x8e, 0x79, 0x27, 0xbd }}, (CREATE_FUNC)caxSimpleObjectImp::New }
};

//-------------------------------------------------------------------------
extern "C" ImplementationProxy* SimpleObjectGetImplementationProxy(int & aTableCount) {
    aTableCount = sizeof(ImplementationTable) / sizeof(ImplementationProxy);
    return ImplementationTable;
}
