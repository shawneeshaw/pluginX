#include "dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
static dtkSimpleCriticalSection TimeStampCritSec;

//-----------------------------------------------------------------------------
// class dtkTimeStamp
//-----------------------------------------------------------------------------
//
dtkTimeStamp * dtkTimeStamp::New() {
    return new dtkTimeStamp;
}

//-----------------------------------------------------------------------------
void dtkTimeStamp::Modified() {
    static unsigned long dtkTimeStampTime = 0;
    TimeStampCritSec.Lock();
    this->ModifiedTime = ++dtkTimeStampTime;
    TimeStampCritSec.Unlock();
}
