#ifndef ARITHMETIC_H
#define ARITHMETIC_H

int  calc_add(int a, int b);
int  calc_sub(int a, int b);
int  calc_mul(int a, int b);
/* 戻り値: 1=成功(成功時のみ result に格納), 0=エラー(ゼロ除算またはresultがNULL) */
int  calc_div(int a, int b, double *result);

#endif /* ARITHMETIC_H */
