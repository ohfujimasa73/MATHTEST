#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "arithmetic.h"

/* テスト結果を保持する構造体（グローバル変数を排除） */
typedef struct {
    int passed;
    int failed;
} TestResult;

static void check_int(TestResult *r, const char *name, int expected, int actual)
{
    if (expected == actual) {
        printf("[PASS] %s: %d\n", name, actual);
        r->passed++;
    } else {
        printf("[FAIL] %s: expected=%d, actual=%d\n", name, expected, actual);
        r->failed++;
    }
}

static void check_double(TestResult *r, const char *name, double expected, double actual, double tol)
{
    if (fabs(expected - actual) <= tol) {
        printf("[PASS] %s: %.4f\n", name, actual);
        r->passed++;
    } else {
        printf("[FAIL] %s: expected=%.4f, actual=%.4f\n", name, expected, actual);
        r->failed++;
    }
}

static void check_bool(TestResult *r, const char *name, int expected, int actual)
{
    if (expected == actual) {
        printf("[PASS] %s: %d\n", name, actual);
        r->passed++;
    } else {
        printf("[FAIL] %s: expected=%d, actual=%d\n", name, expected, actual);
        r->failed++;
    }
}

int main(void)
{
    TestResult r = {0, 0};
    double result = 0.0;

    printf("=== 加算テスト ===\n");
    check_int(&r, "add( 3,  2)",   5, calc_add( 3,  2));
    check_int(&r, "add(-3,  2)",  -1, calc_add(-3,  2));
    check_int(&r, "add( 0,  0)",   0, calc_add( 0,  0));
    check_int(&r, "add(100,-100)", 0, calc_add(100,-100));

    printf("\n=== 減算テスト ===\n");
    check_int(&r, "sub( 5,  3)",  2, calc_sub( 5,  3));
    check_int(&r, "sub( 3,  5)", -2, calc_sub( 3,  5));
    check_int(&r, "sub( 0,  0)",  0, calc_sub( 0,  0));
    check_int(&r, "sub(-4, -4)",  0, calc_sub(-4, -4));

    printf("\n=== 乗算テスト ===\n");
    check_int(&r, "mul( 3,  4)", 12, calc_mul( 3,  4));
    check_int(&r, "mul(-3,  4)",-12, calc_mul(-3,  4));
    check_int(&r, "mul( 0, 99)",  0, calc_mul( 0, 99));
    check_int(&r, "mul(-5, -5)", 25, calc_mul(-5, -5));

    printf("\n=== 除算テスト ===\n");
    result = 0.0;
    check_bool  (&r, "div(10, 2) ret", 1,   calc_div(10, 2, &result));
    check_double(&r, "div(10, 2) val", 5.0, result, 1e-9);

    result = 0.0;
    check_bool  (&r, "div(10, 3) ret", 1,      calc_div(10, 3, &result));
    check_double(&r, "div(10, 3) val", 3.3333, result, 1e-4);

    result = 0.0;
    check_bool  (&r, "div( 0, 5) ret", 1,   calc_div( 0, 5, &result));
    check_double(&r, "div( 0, 5) val", 0.0, result, 1e-9);

    check_bool(&r, "div( 5, 0) ret", 0, calc_div( 5, 0, &result)); /* ゼロ除算 */
    check_bool(&r, "div( 5, 0, NULL) ret", 0, calc_div( 5, 0, NULL)); /* NULLポインタ */
    check_bool(&r, "div( 5, 2, NULL) ret", 0, calc_div( 5, 2, NULL)); /* NULLポインタ(正常除数) */

    result = 0.0;
    check_bool  (&r, "div(-9, 3) ret",  1,    calc_div(-9, 3, &result));
    check_double(&r, "div(-9, 3) val", -3.0,  result, 1e-9);

    result = 0.0;
    check_bool  (&r, "div(-7,-2) ret",  1,    calc_div(-7, -2, &result));
    check_double(&r, "div(-7,-2) val",  3.5,  result, 1e-9);

    printf("\n=== 境界値テスト ===\n");
    check_int(&r, "add(INT_MAX, 0)",  INT_MAX, calc_add(INT_MAX,  0));
    check_int(&r, "add(INT_MIN, 0)",  INT_MIN, calc_add(INT_MIN,  0));
    check_int(&r, "sub(INT_MIN, 0)",  INT_MIN, calc_sub(INT_MIN,  0));
    check_int(&r, "sub(INT_MAX, 0)",  INT_MAX, calc_sub(INT_MAX,  0));
    check_int(&r, "mul(INT_MAX, 1)",  INT_MAX, calc_mul(INT_MAX,  1));
    check_int(&r, "mul(INT_MIN, 1)",  INT_MIN, calc_mul(INT_MIN,  1));
    check_int(&r, "mul( 0, INT_MAX)",       0, calc_mul(0, INT_MAX));

    result = 0.0;
    check_bool  (&r, "div(INT_MAX, INT_MAX) ret", 1,   calc_div(INT_MAX, INT_MAX, &result));
    check_double(&r, "div(INT_MAX, INT_MAX) val", 1.0, result, 1e-9);

    result = 0.0;
    check_bool  (&r, "div(INT_MIN, INT_MIN) ret", 1,   calc_div(INT_MIN, INT_MIN, &result));
    check_double(&r, "div(INT_MIN, INT_MIN) val", 1.0, result, 1e-9);

    result = 0.0;
    check_bool  (&r, "div(INT_MIN, 1) ret",  1,              calc_div(INT_MIN, 1, &result));
    check_double(&r, "div(INT_MIN, 1) val", (double)INT_MIN, result, 1e-0);

    printf("\n=== テスト結果 ===\n");
    printf("合格: %d / 不合格: %d / 合計: %d\n", r.passed, r.failed, r.passed + r.failed);

    return (r.failed == 0) ? 0 : 1;
}
