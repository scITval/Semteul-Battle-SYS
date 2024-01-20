#include "func.h"

#include <stdio.h>

int problemNumber; // 문제 고유 번호
int submitNumber;  // 제출 번호
int language;      // 제출 언어
int timeLimit;     // 시간 제한
int memLimit;      // 메모리 제한

int main(void) {
    init();
    printf("%s\n", get_compile_directory());

    return 0;
}