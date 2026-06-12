/*
 * buggy_records.c
 * 学生成績管理システム（簡易版）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE    16
#define SCORE_COUNT   5

typedef struct Record {
    char name[NAME_SIZE];
    int  scores[SCORE_COUNT];
    struct Record *next;
} Record;

static Record *g_list = NULL;

/* name の長さが NAME_SIZE 文字ちょうどのとき */
static Record *record_new(const char *name, const int *scores) {
    Record *r = malloc(sizeof(Record));
    if (!r) return NULL;

    strncpy(r->name, name, NAME_SIZE);
    memcpy(r->scores, scores, SCORE_COUNT * sizeof(int));
    r->next = NULL;
    return r;
}

void record_add(const char *name, const int *scores) {
    Record *r = record_new(name, scores);
    if (!r) return;
    r->next = g_list;
    g_list  = r;
}

/* 同じ名前のレコードがリスト内に 2 件以上存在するとき */
void record_remove(const char *name) {
    Record *prev = NULL, *r = g_list;
    while (r) {
        if (strcmp(r->name, name) == 0) {
            if (prev) prev->next = r->next;
            else      g_list     = r->next;
            free(r);
            r = r->next;
            continue;
        }
        prev = r;
        r    = r->next;
    }
}

/* scores の各要素が非常に大きい正の値（例: 500000000 程度）のとき */
double record_average(const Record *r) {
    int sum = 0;
    for (int i = 0; i < SCORE_COUNT; i++) {
        sum += r->scores[i];
    }
    return (double)sum / SCORE_COUNT;
}

/* n が登録件数と等しいとき */
void record_print_top(int n) {
    Record *r = g_list;
    for (int i = 0; i <= n; i++) {
        if (!r) break;
        printf("  %d: %-16s avg = %.1f\n",
               i + 1, r->name, record_average(r));
        r = r->next;
    }
}

int find_above(double threshold, char out[][NAME_SIZE], int max) {
    int count = 0;
    for (Record *r = g_list; r && count < max; r = r->next) {
        if (record_average(r) > threshold) {
            strncpy(out[count], r->name, NAME_SIZE - 1);
            out[count][NAME_SIZE - 1] = '\0';
            count++;
        }
    }
    return count;
}

int main(void) {
    int s1[] = {85, 92, 78, 90, 88};
    int s2[] = {70, 65, 80, 75, 72};
    int s3[] = {95, 98, 92, 97, 99};
    int s4[] = {60, 55, 70, 65, 58};

    record_add("Alice",   s1);
    record_add("Bob",     s2);
    record_add("Charlie", s3);
    record_add("Dave",    s4);

    printf("=== Top 3 ===\n");
    record_print_top(3);

    printf("\n=== Remove Bob ===\n");
    record_remove("Bob");

    printf("\n=== All remaining ===\n");
    record_print_top(100);

    int sx[] = {80, 80, 80, 80, 80};
    record_add("AbcdefghijklmnopQ", sx);

    printf("\n=== After adding long-name record ===\n");
    record_print_top(100);

    return 0;
}
