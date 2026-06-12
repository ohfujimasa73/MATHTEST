#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "arithmetic.h"

static int run_cli(FILE *input, FILE *output)
{
	int a = 0;
	int b = 0;
	char op = 0;
	double result = 0.0;

	fprintf(output, "1つ目の整数を入力してください: ");
	fflush(output);
	fscanf(input, "%d", &a);

	fprintf(output, "演算子を入力してください (+, -, *, /): ");
	fflush(output);
	fscanf(input, " %c", &op);

	fprintf(output, "2つ目の整数を入力してください: ");
	fflush(output);
	fscanf(input, "%d", &b);

	switch (op) {
		case '+':
			fprintf(output, "結果: %d + %d = %d\n", a, b, calc_add(a, b));
			break;
		case '-':
			fprintf(output, "結果: %d - %d = %d\n", a, b, calc_sub(a, b));
			break;
		case '*':
			fprintf(output, "結果: %d * %d = %d\n", a, b, calc_mul(a, b));
			break;
		case '/':
			if (!calc_div(a, b, &result)) {
				fprintf(output, "エラー: 0で割ることはできません\n");
			} else {
				fprintf(output, "結果: %d / %d = %.2f\n", a, b, result);
			}
			break;
		default:
			fprintf(output, "エラー: 無効な演算子です\n");
			break;
	}

	return 0;
}

int main(void)
{
	return run_cli(stdin, stdout);
}
