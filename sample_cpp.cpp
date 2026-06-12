#include <stdio.h>
#include "arithmetic.h"

/* C言語の算術ライブラリをC++から呼び出すサンプル */

int main()
{
    /* 加算・減算・乗算 */
    printf("=== 加算 ===\n");
    printf("calc_add(10, 3)  = %d\n", calc_add(10, 3));
    printf("calc_add(-5, 5)  = %d\n", calc_add(-5, 5));

    printf("\n=== 減算 ===\n");
    printf("calc_sub(10, 3)  = %d\n", calc_sub(10, 3));
    printf("calc_sub( 3,10)  = %d\n", calc_sub( 3,10));

    printf("\n=== 乗算 ===\n");
    printf("calc_mul( 6, 7)  = %d\n", calc_mul( 6, 7));
    printf("calc_mul(-3, 4)  = %d\n", calc_mul(-3, 4));

    /* 除算: 戻り値でエラー判定 */
    printf("\n=== 除算 ===\n");
    double result = 0.0;

    if (calc_div(10, 4, &result)) {
        printf("calc_div(10, 4)  = %f\n", result);
    }

    if (calc_div(7, 3, &result)) {
        printf("calc_div( 7, 3)  = %f\n", result);
    }

    /* ゼロ除算エラー */
    if (!calc_div(5, 0, &result)) {
        printf("calc_div( 5, 0)  -> エラー: ゼロ除算\n");
    }

    /* NULLポインタエラー */
    if (!calc_div(5, 2, nullptr)) {
        printf("calc_div( 5, 2, nullptr) -> エラー: NULLポインタ\n");
    }

    return 0;
}
