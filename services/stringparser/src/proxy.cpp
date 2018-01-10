// ServiceStringParser.cpp : Defines the entry point for the DLL application.
//
#include <assert.h>
#include <stdio.h>
#include <cpl.h>
#include "caxservicestringparser.h"
#include "caxservicestringparserimp.h"

//-------------------------------------------------------------------------
static ImplementationProxy ImplementationTable[] = {
    {"3C561AE4-0912-43bb-8CF0-AFB88E7927BD", {0x3c561ae4, 0x912, 0x43bb, { 0x8c, 0xf0, 0xaf, 0xb8, 0x8e, 0x79, 0x27, 0xbd }}, (CREATE_FUNC)caxServiceStringParserImp::New }
};

//-------------------------------------------------------------------------
extern "C" ImplementationProxy* CoGetImplementationProxy(int & aTableCount) {
    aTableCount = sizeof(ImplementationTable) / sizeof(ImplementationProxy);
    return ImplementationTable;
}

//-------------------------------------------------------------------------
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
