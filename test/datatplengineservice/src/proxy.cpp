// ServiceStringParser.cpp : Defines the entry point for the DLL application.
//
#include <assert.h>
#include <stdio.h>
#include <cpl.h>
#include "caxservicedatatplengine.h"
#include "caxservicedatatplengineimp.h"

//-------------------------------------------------------------------------
static ImplementationProxy ImplementationTable[] = {
    {"285525E9-8410-43fa-BB7F-9F3A07AB9E67", {0x285525e9, 0x8410, 0x43fa, { 0xbb, 0x7f, 0x9f, 0x3a, 0x7, 0xab, 0x9e, 0x67 }}, (CREATE_FUNC)caxServiceDataTPLEngineImp::New }
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
