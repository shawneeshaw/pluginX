#ifndef DTKCRITICALSECTION_H
#define DTKCRITICALSECTION_H

#ifdef MTK_USE_SPROC
#include <abi_mutex.h>
typedef abilock_t dtkCritSecType;
#endif

#ifdef MTK_USE_PTHREADS
#include <pthread.h>
typedef pthread_mutex_t dtkCritSecType;
#endif

#ifdef _WIN32
#include <winbase.h>
typedef CRITICAL_SECTION dtkCritSecType;
#endif

#ifndef MTK_USE_SPROC
#ifndef MTK_USE_PTHREADS
#ifndef _WIN32
typedef int dtkCritSecType;

#endif
#endif
#endif

class dtkSimpleCriticalSection {
public:
    /** create instance */
    static dtkSimpleCriticalSection * New();

    /** delete itself */
    void Delete() { delete this; }

    /** lock the dtkCriticalSection */
    void Lock(void);

    /** unlock the dtkCriticalSection */
    void Unlock(void);

public:
    /** constructor */
    dtkSimpleCriticalSection();

    /** destructor */
    virtual ~dtkSimpleCriticalSection();

protected:
    dtkCritSecType CritSec;
};

class dtkCriticalSection {
public:
    /** create instance */
    static dtkCriticalSection * New();

    /** lock the dtkCriticalSection */
    void Lock(void);

    /** unlock the dtkCriticalSection */
    void Unlock(void);

protected:
    dtkSimpleCriticalSection SimpleCriticalSection;
};

//-----------------------------------------------------------------------------
inline void dtkCriticalSection::Lock(void) {
    this->SimpleCriticalSection.Lock();
}

//-----------------------------------------------------------------------------
inline void dtkCriticalSection::Unlock(void) {
    this->SimpleCriticalSection.Unlock();
}

#endif //DTKCRITICALSECTION_H
