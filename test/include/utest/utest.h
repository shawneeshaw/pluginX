#ifndef UTESTLIB_H
#define UTESTLIB_H

#ifndef UTESTAPI
#define UTESTAPI __declspec(dllimport)
#endif 

/******************************************************************************\
 *
 *                    test system: test case function pointer.
 *
\******************************************************************************/

typedef void (*TESTCASEFP) ();

/******************************************************************************\
 *
 *                    test system: initialization/shutdown.
 *
\******************************************************************************/

/** U-test library: initialize */
UTESTAPI int UTestInit();

/** U-test library: shutdown */
UTESTAPI int UTestShutDown();

/******************************************************************************\
 *
 *                    test system: add test.
 *
\******************************************************************************/

/** U-test library: add test */
UTESTAPI int UTestAdd(const char* fname, long lineno, const char* casename, TESTCASEFP tc);

/** U-test library: run */
UTESTAPI int UTestRun();

/** U-test library: assert */
UTESTAPI int UAssert(const char* const fname, long lineno, int actual, int expected);

/** U-test library: assert */
UTESTAPI int UAssert(const char* const fname, long lineno, const char* actual, const char* expected);

/******************************************************************************\
 *
 *                    test system: macro definitions.
 *
\******************************************************************************/

//assert any failing case
#define utassert(actual, expected) UAssert(__FILE__, __LINE__, actual, expected)

//test definition.
#define TEST(s) \
void Test##s(); \
const int __TestAA##s = UTestAdd(__FILE__, __LINE__, #s, Test##s); \
void Test##s()

#define UTEST_GLOBAL

#endif //UTESTLIB_H
