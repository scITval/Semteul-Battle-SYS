#include "grade.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int problemNumber; // 문제 고유 번호
int submitNumber;  // 제출 번호
char language[30];      // 제출 언어
// char *language;      // 제출 언어
int timeLimit;     // 시간 제한
int memLimit;      // 메모리 제한

void ForTest(void) {
    problemNumber = 12345;
    submitNumber = 5;
    strcpy(language, "java");
    timeLimit = 100;
    memLimit = 4096;
}

int Grade(void) {
    ForTest();
    printf("문제 번호: %d\n제출 번호: %d\n제출 언어: %s\n시간 제한: %d\n메모리 제한: %d\n", problemNumber, submitNumber, language, timeLimit, memLimit);

    char str1[100];
    char *str2;
    char str3[30];
    strcpy(str1, language);
    printf("str1: %s\n", str1);
    str2 = str1;
    printf("str2: %s\n", str2);
    strcpy(str3, language);
    printf("str3: %s\n", str3);
    return 5;
}