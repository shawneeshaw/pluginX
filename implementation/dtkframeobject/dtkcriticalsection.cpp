#include "dtkframeobjectincludes.h"

//-----------------------------------------------------------------------------
// class dtkCriticalSection
//-----------------------------------------------------------------------------
//
dtkCriticalSection * dtkCriticalSection::New() {
    return new dtkCriticalSection;
}

//-----------------------------------------------------------------------------
// class dtkSimpleCriticalSection
//-----------------------------------------------------------------------------
//
dtkSimpleCriticalSection::dtkSimpleCriticalSection() {
#ifdef MTK_USE_SPROC
    init_lock(& this->CritSec);
#endif

#ifdef _WIN32
    InitializeCriticalSection(& this->CritSec);
#endif

#ifdef MTK_USE_PTHREADS
#ifdef MTK_HP_PTHREADS
    pthread_mutex_init(& (this->CritSec), pthread_mutexattr_default);
#else
    pthread_mutex_init(& (this->CritSec), NULL);
#endif
#endif

}

//-----------------------------------------------------------------------------
dtkSimpleCriticalSection::~dtkSimpleCriticalSection() {
#ifdef _WIN32
    DeleteCriticalSection(& this->CritSec);
#endif

#ifdef MTK_USE_PTHREADS
    pthread_mutex_destroy(& this->CritSec);
#endif
}

//-----------------------------------------------------------------------------
void dtkSimpleCriticalSection::Lock() {
#ifdef MTK_USE_SPROC
    spin_lock(& this->CritSec);
#endif

#ifdef _WIN32
    EnterCriticalSection(& this->CritSec);
#endif

#ifdef MTK_USE_PTHREADS
    pthread_mutex_lock(& this->CritSec);
#endif
}

//-----------------------------------------------------------------------------
void dtkSimpleCriticalSection::Unlock() {
#ifdef MTK_USE_SPROC
    release_lock(& this->CritSec);
#endif

#ifdef _WIN32
    LeaveCriticalSection(& this->CritSec);
#endif

#ifdef MTK_USE_PTHREADS
    pthread_mutex_unlock(& this->CritSec);
#endif
}
