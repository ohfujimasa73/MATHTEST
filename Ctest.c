#include <stdio.h>
#include "arithmetic.h"

int main(void)
{
	int a = 0;
	int b = 0;
	char op = 0;
	double result = 0.0;

	printf("1つ目の整数を入力してください: ");
	fflush(stdout);
	scanf("%d", &a);

	printf("演算子を入力してください (+, -, *, /): ");
	fflush(stdout);
	scanf(" %c", &op);

	printf("2つ目の整数を入力してください: ");
	fflush(stdout);
	scanf("%d", &b);

	switch (op) {
		case '+':
			printf("結果: %d + %d = %d\n", a, b, calc_add(a, b));
			break;
		case '-':
			printf("結果: %d - %d = %d\n", a, b, calc_sub(a, b));
			break;
		case '*':
			printf("結果: %d * %d = %d\n", a, b, calc_mul(a, b));
			break;
		case '/':
			if (!calc_div(a, b, &result)) {
				printf("エラー: 0で割ることはできません\n");
			} else {
				printf("結果: %d / %d = %.2f\n", a, b, result);
			}
			break;
		default:
			printf("エラー: 無効な演算子です\n");
			break;
	}

	return 0;
}
