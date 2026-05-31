#include <stdio.h>
#include <math.h>
#include "arithmetic.h"

static int passed = 0;
static int failed = 0;

static void check_int(const char *name, int expected, int actual)
{
    if (expected == actual) {
        printf("[PASS] %s: %d\n", name, actual);
        passed++;
    } else {
        printf("[FAIL] %s: expected=%d, actual=%d\n", name, expected, actual);
        failed++;
    }
}

static void check_double(const char *name, double expected, double actual, double tol)
{
    if (fabs(expected - actual) <= tol) {
        printf("[PASS] %s: %.4f\n", name, actual);
        passed++;
    } else {
        printf("[FAIL] %s: expected=%.4f, actual=%.4f\n", name, expected, actual);
        failed++;
    }
}

static void check_bool(const char *name, int expected, int actual)
{
    if (expected == actual) {
        printf("[PASS] %s: %d\n", name, actual);
        passed++;
    } else {
        printf("[FAIL] %s: expected=%d, actual=%d\n", name, expected, actual);
        failed++;
    }
}

int main(void)
{
    double result = 0.0;

    printf("=== 加算テスト ===\n");
    check_int("add( 3,  2)",  5, calc_add( 3,  2));
    check_int("add(-3,  2)", -1, calc_add(-3,  2));
    check_int("add( 0,  0)",  0, calc_add( 0,  0));
    check_int("add(100,-100)",0, calc_add(100,-100));

    printf("\n=== 減算テスト ===\n");
    check_int("sub( 5,  3)",  2, calc_sub( 5,  3));
    check_int("sub( 3,  5)", -2, calc_sub( 3,  5));
    check_int("sub( 0,  0)",  0, calc_sub( 0,  0));
    check_int("sub(-4, -4)",  0, calc_sub(-4, -4));

    printf("\n=== 乗算テスト ===\n");
    check_int("mul( 3,  4)", 12, calc_mul( 3,  4));
    check_int("mul(-3,  4)",-12, calc_mul(-3,  4));
    check_int("mul( 0, 99)",  0, calc_mul( 0, 99));
    check_int("mul(-5, -5)", 25, calc_mul(-5, -5));

    printf("\n=== 除算テスト ===\n");
    result = 0.0;
    check_bool("div(10, 2) ret", 1, calc_div(10, 2, &result));
    check_double("div(10, 2) val", 5.0, result, 1e-9);

    result = 0.0;
    check_bool("div(10, 3) ret", 1, calc_div(10, 3, &result));
    check_double("div(10, 3) val", 3.3333, result, 1e-4);

    result = 0.0;
    check_bool("div( 0, 5) ret", 1, calc_div( 0, 5, &result));
    check_double("div( 0, 5) val", 0.0, result, 1e-9);

    check_bool("div( 5, 0) ret", 0, calc_div( 5, 0, &result)); /* ゼロ除算 */

    printf("\n=== テスト結果 ===\n");
    printf("合格: %d / 不合格: %d / 合計: %d\n", passed, failed, passed + failed);

    return (failed == 0) ? 0 : 1;
}
