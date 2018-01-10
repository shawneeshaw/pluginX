#ifndef DTKWIN32HEADER_H
#define DTKWIN32HEADER_H

#ifndef __DTK_SYSTEM_INCLUDES__INSIDE
Do_not_include_dtkWin32Header_directly__dtkSystemIncludes_includes_it;
#endif

//
// Windows specific stuff------------------------------------------
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__)

// define strict header for windows
#ifndef STRICT
#define STRICT
#endif
#endif

// MSVC 6.0 in release mode will warn about code it produces with its
// optimizer.  Disable the warnings specifically for this
// configuration.  Real warnings will be revealed by a debug build or
// by other compilers.
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(NDEBUG)
# pragma warning ( disable : 4701 ) /* Variable may be used uninitialized.  */
# pragma warning ( disable : 4702 ) /* Unreachable code.  */
#endif

#endif //DTKWIN32HEADER_H

