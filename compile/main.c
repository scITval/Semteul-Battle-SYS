#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int problemNumber; // 문제 고유 번호
int submitNumber;  // 제출 번호
char language[30];      // 제출 언어
// char *language;      // 제출 언어
int timeLimit;     // 시간 제한
int memLimit;      // 메모리 제한

int main(void) {
    InitDirectory();
    ParseInitFile();
    // printf("문제 번호: %d\n제출 번호: %d\n제출 언어: %s\n시간 제한: %d\n메모리 제한: %d\n", problemNumber, submitNumber, language, timeLimit, memLimit);

    return 0;
}