#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "arithmetic.h"

#define main Ctest_main
#include "Ctest.c"
#undef main

typedef struct {
    int passed;
    int failed;
} TestResult;

static void check_text(TestResult *r, const char *name, const char *expected, const char *actual)
{
    if (strcmp(expected, actual) == 0) {
        printf("[PASS] %s\n", name);
        r->passed++;
    } else {
        printf("[FAIL] %s\n", name);
        printf("  expected: %s\n", expected);
        printf("  actual:   %s\n", actual);
        r->failed++;
    }
}

static int run_case(const char *input, char *output, size_t output_size)
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    int ok = 0;

    input_file = tmpfile();
    output_file = tmpfile();
    if (input_file == NULL || output_file == NULL) {
        goto cleanup;
    }

    if (fputs(input, input_file) == EOF) {
        goto cleanup;
    }
    rewind(input_file);

    run_cli(input_file, output_file);
    fflush(output_file);
    rewind(output_file);

    {
        size_t bytes_read = fread(output, 1, output_size - 1, output_file);
        size_t write_index = 0;

        for (size_t i = 0; i < bytes_read; ++i) {
            if (output[i] != '\r') {
                output[write_index++] = output[i];
            }
        }
        output[write_index] = '\0';
    }
    ok = 1;

cleanup:
    if (input_file != NULL) {
        fclose(input_file);
    }
    if (output_file != NULL) {
        fclose(output_file);
    }

    return ok;
}

int main(void)
{
    TestResult result = {0, 0};
    char actual[1024];

    if (!run_case("3\n+\n4\n", actual, sizeof(actual))) {
        printf("[FAIL] 正常系：加算の実行に失敗しました\n");
        result.failed++;
    } else {
        check_text(&result,
                   "正常系：加算の出力",
                   "1つ目の整数を入力してください: 演算子を入力してください (+, -, *, /): 2つ目の整数を入力してください: 結果: 3 + 4 = 7\n",
                   actual);
    }

    if (!run_case("7\n/\n2\n", actual, sizeof(actual))) {
        printf("[FAIL] 正常系：除算の実行に失敗しました\n");
        result.failed++;
    } else {
        check_text(&result,
                   "正常系：除算の出力",
                   "1つ目の整数を入力してください: 演算子を入力してください (+, -, *, /): 2つ目の整数を入力してください: 結果: 7 / 2 = 3.50\n",
                   actual);
    }

    if (!run_case("8\n/\n0\n", actual, sizeof(actual))) {
        printf("[FAIL] 異常系：ゼロ除算の実行に失敗しました\n");
        result.failed++;
    } else {
        check_text(&result,
                   "異常系：ゼロ除算の出力",
                   "1つ目の整数を入力してください: 演算子を入力してください (+, -, *, /): 2つ目の整数を入力してください: エラー: 0で割ることはできません\n",
                   actual);
    }

    if (!run_case("1\n?\n2\n", actual, sizeof(actual))) {
        printf("[FAIL] 異常系：無効演算子の実行に失敗しました\n");
        result.failed++;
    } else {
        check_text(&result,
                   "異常系：無効演算子の出力",
                   "1つ目の整数を入力してください: 演算子を入力してください (+, -, *, /): 2つ目の整数を入力してください: エラー: 無効な演算子です\n",
                   actual);
    }

    printf("\n=== Ctest.c テスト結果 ===\n");
    printf("合格: %d / 不合格: %d / 合計: %d\n", result.passed, result.failed, result.passed + result.failed);

    return (result.failed == 0) ? 0 : 1;
}