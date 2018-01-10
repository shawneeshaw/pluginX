// SimpleService.cpp : Defines the entry point for the DLL application.
//
#include <assert.h>
#include <stdio.h>
#include <cpl.h>
#include "caxshape.h"
#include "caxcircle.h"

//-------------------------------------------------------------------------
static ImplementationProxy ImplementationTable[] = {
	{"07559FD3-E558-44ad-A2D3-7658BB8DADEC", {0x7559fd3, 0xe558, 0x44ad, { 0xa2, 0xd3, 0x76, 0x58, 0xbb, 0x8d, 0xad, 0xec }}, (CREATE_FUNC)caxCircle::New }
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
