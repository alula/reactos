/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         Test for sprintf
 * PROGRAMMER:      Thomas Faber <thomas.faber@reactos.org>
 */

#include <apitest.h>
#include <apitest_guard.h>

#define WIN32_NO_STATUS
#include <stdio.h>
#include <tchar.h>
#include <float.h>
#include <pseh/pseh2.h>
#include <ndk/mmfuncs.h>
#include <ndk/rtlfuncs.h>

#ifdef _MSC_VER
#pragma warning(disable:4778) // unterminated format string '%'
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wnonnull"
#if __GNUC__ >= 7
#pragma GCC diagnostic ignored "-Wformat-overflow"
#endif
#endif

#undef assert
#if DBG
#define assert(x) if (!(x)) __int2c()
#else
#define assert(x)
#endif

#define ok_sprintf_1_(line, format, arg, expected) \
{ \
    char buffer[500]; \
    int len = sprintf(buffer, format, arg); \
    assert(len < _countof(buffer)); \
    int expected_len = (int)strlen(expected); \
    ok_str_(__FILE__, line, buffer, expected); \
    ok_int_(__FILE__, line, len, expected_len); \
}

#define ok_sprintf_1(format, arg, expected) \
    ok_sprintf_1_(__LINE__, format, arg, expected)

static void test_basic(void)
{
    int Length;
    CHAR Buffer[128];

    /* basic parameter tests */
    StartSeh()
        Length = sprintf(NULL, NULL);
    EndSeh(STATUS_ACCESS_VIOLATION);

    StartSeh()
        Length = sprintf(NULL, "");
        ok_int(Length, 0);
#if TEST_CRTDLL || TEST_USER32
    EndSeh(STATUS_ACCESS_VIOLATION);
#else
    EndSeh(STATUS_SUCCESS);
#endif

    StartSeh()
        Length = sprintf(NULL, "Hello");
        ok_int(Length, 5);
#if TEST_CRTDLL || TEST_USER32
    EndSeh(STATUS_ACCESS_VIOLATION);
#else
    EndSeh(STATUS_SUCCESS);
#endif

    /* some basic formats */
    Length = sprintf(Buffer, "abcde");
    ok_str(Buffer, "abcde");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%%");
    ok_str(Buffer, "%");
    ok_int(Length, 1);

    Length = sprintf(Buffer, "%");
    ok_str(Buffer, "");
    ok_int(Length, 0);

    Length = sprintf(Buffer, "%%%");
    ok_str(Buffer, "%");
    ok_int(Length, 1);
}

static void test_int_d(void)
{
    ok_sprintf_1("%d", 8, "8");

}

static void test_string(void)
{
    int Length;
    CHAR Buffer[128];
    PCHAR String;

    Length = sprintf(Buffer, "%s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    /* field width for %s */
    Length = sprintf(Buffer, "%8s", "hello");
    ok_str(Buffer, "   hello");
    ok_int(Length, 8);

    Length = sprintf(Buffer, "%4s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%-8s", "hello");
    ok_str(Buffer, "hello   ");
    ok_int(Length, 8);

    Length = sprintf(Buffer, "%-5s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%0s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%-0s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%*s", -8, "hello");
#ifdef TEST_USER32
    ok_str(Buffer, "*s");
    ok_int(Length, 2);
#else
    ok_str(Buffer, "hello   ");
    ok_int(Length, 8);
#endif

    /* precision for %s */
    Length = sprintf(Buffer, "%.s", "hello");
    ok_str(Buffer, "");
    ok_int(Length, 0);

    Length = sprintf(Buffer, "%.0s", "hello");
    ok_str(Buffer, "");
    ok_int(Length, 0);

    Length = sprintf(Buffer, "%.10s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%.5s", "hello");
    ok_str(Buffer, "hello");
    ok_int(Length, 5);

    Length = sprintf(Buffer, "%.4s", "hello");
    ok_str(Buffer, "hell");
    ok_int(Length, 4);

    StartSeh()
        Length = sprintf(Buffer, "%.*s", -1, "hello");
#ifdef TEST_USER32
        ok_str(Buffer, "*s");
        ok_int(Length, 2);
#else
        ok_str(Buffer, "hello");
        ok_int(Length, 5);
#endif
    EndSeh(STATUS_SUCCESS);

    String = AllocateGuarded(6);
    if (!String)
    {
        skip("Guarded allocation failure\n");
        return;
    }

    strcpy(String, "hello");
    StartSeh()
        Length = sprintf(Buffer, "%.8s", String);
        ok_str(Buffer, "hello");
        ok_int(Length, 5);
    EndSeh(STATUS_SUCCESS);

    StartSeh()
        Length = sprintf(Buffer, "%.6s", String);
        ok_str(Buffer, "hello");
        ok_int(Length, 5);
    EndSeh(STATUS_SUCCESS);

    StartSeh()
        Length = sprintf(Buffer, "%.5s", String);
        ok_str(Buffer, "hello");
        ok_int(Length, 5);
    EndSeh(STATUS_SUCCESS);

    StartSeh()
        Length = sprintf(Buffer, "%.4s", String);
        ok_str(Buffer, "hell");
        ok_int(Length, 4);
    EndSeh(STATUS_SUCCESS);

    String[5] = '!';
    StartSeh()
        Length = sprintf(Buffer, "%.5s", String);
        ok_str(Buffer, "hello");
        ok_int(Length, 5);
#ifdef TEST_USER32
    EndSeh(STATUS_ACCESS_VIOLATION);
#else
    EndSeh(STATUS_SUCCESS);
#endif

    StartSeh()
        Length = sprintf(Buffer, "%.6s", String);
        ok_str(Buffer, "hello!");
        ok_int(Length, 6);
#ifdef TEST_USER32
    EndSeh(STATUS_ACCESS_VIOLATION);
#else
    EndSeh(STATUS_SUCCESS);
#endif

    StartSeh()
        Length = sprintf(Buffer, "%.*s", 5, String);
#ifdef TEST_USER32
        ok_str(Buffer, "*s");
        ok_int(Length, 2);
#else
        ok_str(Buffer, "hello");
        ok_int(Length, 5);
#endif
    EndSeh(STATUS_SUCCESS);

    StartSeh()
        Length = sprintf(Buffer, "%.*s", 6, String);
#ifdef TEST_USER32
        ok_str(Buffer, "*s");
        ok_int(Length, 2);
#else
        ok_str(Buffer, "hello!");
        ok_int(Length, 6);
#endif
    EndSeh(STATUS_SUCCESS);

    /* both field width and precision */
    StartSeh()
        Length = sprintf(Buffer, "%8.5s", String);
        ok_str(Buffer, "   hello");
        ok_int(Length, 8);
#ifdef TEST_USER32
    EndSeh(STATUS_ACCESS_VIOLATION);
#else
    EndSeh(STATUS_SUCCESS);
#endif

    StartSeh()
        Length = sprintf(Buffer, "%-*.6s", -8, String);
#ifdef TEST_USER32
        ok_str(Buffer, "*.6s");
        ok_int(Length, 4);
#else
        ok_str(Buffer, "hello!  ");
        ok_int(Length, 8);
#endif
    EndSeh(STATUS_SUCCESS);

    StartSeh()
        Length = sprintf(Buffer, "%*.*s", -8, 6, String);
#ifdef TEST_USER32
        ok_str(Buffer, "*.*s");
        ok_int(Length, 4);
#else
        ok_str(Buffer, "hello!  ");
        ok_int(Length, 8);
#endif
    EndSeh(STATUS_SUCCESS);

    FreeGuarded(String);
}


//
// Floating point values.
// The format pecifier: "%[flags][width][.precision][length]specifier"
// flags: '-', '+', ' ', '#', '0'
// specifier: 'e', 'E', 'f', 'F', 'g', 'G', 'a', 'A'
//
// The results is printed as:
// [left_ws_padding][sign][left_0_padding][integer_significant][integer_0_pad][.][fraction_significant][fraction_0_pad]
//

static const UINT64 g_Inf = 0x7FF0000000000000ULL;
static const UINT64 g_NegInf = 0xFFF0000000000000ULL;
static const UINT64 g_NaN1 = 0x7FF0000000000001ULL;
static const UINT64 g_NaN2 = 0x7FF8000000000001ULL;
static const UINT64 g_NaN3 = 0x7FFFFFFFFFFFFFFFULL;
static const UINT64 g_NaN4 = 0x7FF80000000000F1ULL;
static const UINT64 g_NegNaN1 = 0xFFF0000000000001ULL;

void test_float_f(void)
{
    ok_sprintf_1("%f", 0.0, "0.000000");
    ok_sprintf_1("%f", 1.0, "1.000000");
    ok_sprintf_1("%f", -1.0, "-1.000000");
    ok_sprintf_1("%f", 1.23456789, "1.234568");
    ok_sprintf_1("%f", 0.00123456789, "0.001235");
    ok_sprintf_1("%f", FLT_MAX, "340282346638528860000000000000000000000.000000");
    ok_sprintf_1("%f", DBL_MAX, "179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000");
    ok_sprintf_1("% f", 1.0, " 1.000000");
    ok_sprintf_1("% f", -1.0, "-1.000000");
    ok_sprintf_1("%4f", 1.0, "1.000000");
    ok_sprintf_1("%8f", 1.0, "1.000000");
    ok_sprintf_1("%9f", 1.0, " 1.000000");
    ok_sprintf_1("% 9f", 1.0, " 1.000000");
    ok_sprintf_1("%9f", -1.0, "-1.000000");
    ok_sprintf_1("%10f", -1.0, " -1.000000");
    ok_sprintf_1("% 10f", -1.0, " -1.000000");
    ok_sprintf_1("%0f", 1.0, "1.000000");
    ok_sprintf_1("%010f", -1.0, "-01.000000");
    ok_sprintf_1("%.0f", 0.6, "1");
    ok_sprintf_1("%.0f", 1.23456789, "1");
    ok_sprintf_1("%.3f", 1.23456789, "1.235");
    ok_sprintf_1("%.11f", 1.23456789, "1.23456789000");

    ok_sprintf_1("%f", -123.45678, "-123.456780");
    ok_sprintf_1("%f", -9.2559631349317830737e+061, "-92559631349317831000000000000000000000000000000000000000000000.000000");

    ok_sprintf_1("%f", *(double*)&g_Inf, "1.#INF00");
    ok_sprintf_1("%f", *(double*)&g_NegInf, "-1.#INF00");
    ok_sprintf_1("%f", *(double*)&g_NaN1, "1.#SNAN0");
    ok_sprintf_1("%f", *(double*)&g_NegNaN1, "-1.#SNAN0");
    ok_sprintf_1("%f", *(double*)&g_NaN2, "1.#QNAN0");
    ok_sprintf_1("%f", *(double*)&g_NaN3, "1.#QNAN0");
    ok_sprintf_1("%f", *(double*)&g_NaN4, "1.#QNAN0");
    ok_sprintf_1("%10f", *(double*)&g_Inf, "  1.#INF00");
    ok_sprintf_1("%.10f", *(double*)&g_Inf, "1.#INF000000");
    ok_sprintf_1("%.0f", *(double*)&g_Inf, "1");

    // %lf (same as %f)
    ok_sprintf_1("%lf", 0.0, "0.000000");
    ok_sprintf_1("%lf", 1.0, "1.000000");
    ok_sprintf_1("%lf", -1.0, "-1.000000");
    ok_sprintf_1("%lf", -123.45678, "-123.456780");


}

void test_float_e(void)
{
    ok_sprintf_1("%e", 1.0, "1.000000e+000");
    ok_sprintf_1("% 13e", 1.0, " 1.000000e+000");
    ok_sprintf_1("% 14e", 1.0, " 1.000000e+000");
    ok_sprintf_1("% 15e", 1.0, "  1.000000e+000");
    ok_sprintf_1("%013e", 1.0, "1.000000e+000");
    ok_sprintf_1("%014e", 1.0, "01.000000e+000");
    ok_sprintf_1("%015e", 1.0, "001.000000e+000");
    ok_sprintf_1("%.0e", 1.23456789, "1e+000");
    ok_sprintf_1("%.3e", 1.23456789, "1.235e+000");
    ok_sprintf_1("%.11e", 1.23456789, "1.23456789000e+000");

    ok_sprintf_1("%e", *(double*)&g_Inf, "1.#INF00e+000");
    ok_sprintf_1("%e", *(double*)&g_NegInf, "-1.#INF00e+000");
    ok_sprintf_1("%e", *(double*)&g_NaN1, "1.#SNAN0e+000");
    ok_sprintf_1("%e", *(double*)&g_NegNaN1, "-1.#SNAN0e+000");
    ok_sprintf_1("%e", *(double*)&g_NaN2, "1.#QNAN0e+000");
    ok_sprintf_1("%e", *(double*)&g_NaN3, "1.#QNAN0e+000");
    ok_sprintf_1("%e", *(double*)&g_NaN4, "1.#QNAN0e+000");
    ok_sprintf_1("%14e", *(double*)&g_Inf, " 1.#INF00e+000");
    ok_sprintf_1("%.10e", *(double*)&g_Inf, "1.#INF000000e+000");
    ok_sprintf_1("%.0e", *(double*)&g_Inf, "1e+000");

    char buffer[100];
    int len = sprintf(buffer, "%-+.*E", 3, 999999999999.9);
    ok_str(buffer, "+1.000E+012");
    ok_int(len, 11);
}

void test_float_g(void)
{
    ok_sprintf_1("%.7G", 9.9999999747524270788e-007, "1E-006");

}

/* NOTE: This test is not only used for all the CRT apitests, but also for
 *       user32's wsprintf. Make sure to test them all */
START_TEST(sprintf)
{
    //test_basic();
    //test_int_d();
    //test_string();
    test_float_f();
    test_float_e();
    test_float_g();
}
