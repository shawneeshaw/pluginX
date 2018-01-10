#ifndef CAXDEFINE_H
#define CAXDEFINE_H

//-------------------------------------------------------------------------
typedef struct _DGUID {
    int   Data1;
    short Data2;
    short Data3;
    char  Data4[8];
} DGUID;

#define REFDGUID const DGUID&

//-------------------------------------------------------------------------
typedef void* (*CREATE_FUNC)();

//-------------------------------------------------------------------------
typedef struct _ImplementationProxy {
    char progId[64];
    DGUID classId;
    CREATE_FUNC func;
} 
ImplementationProxy;

typedef ImplementationProxy* (*IMPLEMENTPROXY_FUNC)(int&);

//-------------------------------------------------------------------------
inline BOOL IsEqualDGUID(REFDGUID r1, REFDGUID r2) 
{ return !memcmp(&r1, &r2, sizeof(DGUID)); }

inline BOOL operator == (REFDGUID r1, REFDGUID r2) 
{ return !memcmp(&r1, &r2, sizeof(DGUID)); }

inline BOOL operator != (REFDGUID r1, REFDGUID r2) 
{ return !(r1 == r2); }

#endif //CAXDEFINE_H
