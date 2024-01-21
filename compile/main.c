#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int problemNumber; // 문제 고유 번호
int submitNumber;  // 제출 번호
int language;      // 제출 언어
int timeLimit;     // 시간 제한
int memLimit;      // 메모리 제한

int main(void) {
    init_directory();
    char buf[1024];
    printf("%s\n", getcwd(buf, 1024));
    printf("%s\n%s\n%s\n%s\n", get_home_directory(), get_compile_directory(), get_test_directory(), get_result_directory());

    return 0;
}