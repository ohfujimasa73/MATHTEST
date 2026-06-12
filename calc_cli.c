#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arithmetic.h"

/* 使い方: calc_cli.exe <数値1> <演算子> <数値2>
 * 演算子: add sub mul div
 * 例: calc_cli.exe 10 div 3
 */
int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "使い方: calc_cli.exe <数値1> <演算子> <数値2>\n");
        fprintf(stderr, "演算子: add  sub  mul  div\n");
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[3]);
    double dresult = 0.0;

    if (strcmp(argv[2], "add") == 0) {
        printf("%d\n", calc_add(a, b));
    } else if (strcmp(argv[2], "sub") == 0) {
        printf("%d\n", calc_sub(a, b));
    } else if (strcmp(argv[2], "mul") == 0) {
        printf("%d\n", calc_mul(a, b));
    } else if (strcmp(argv[2], "div") == 0) {
        if (!calc_div(a, b, &dresult)) {
            fprintf(stderr, "エラー: 0で割ることはできません\n");
            return 1;
        }
        if (dresult == (int)dresult)
            printf("%d\n", (int)dresult);
        else
            printf("%.6g\n", dresult);
    } else {
        fprintf(stderr, "エラー: 無効な演算子 '%s'\n", argv[2]);
        return 1;
    }

    return 0;
}
