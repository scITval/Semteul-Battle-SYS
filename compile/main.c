#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    // init.c - 디렉토리 경로 초기화
    InitPath();

    // init.c - ./code/compile/init.txt 파일 내용 읽기
    if (ParseInitFile() == 1) {
        fprintf(stderr, "ParseInitFile() error in init.c\n");
        exit(1);
    }

    // grade.c - 컴파일 결과를 ./code/compile_result.txt에 씀
    if (Compile() == 1) {
        fprintf(stderr, "Compile() error in grade.c\n");
        exit(1);
    }

    // int GradeResult;
    // char *resultStr[] = {"틀림", "맞음", "시간 초과", "메모리 초과", "컴파일 에러", "런타임 에러"};
    // if ((GradeResult = Compile()) < 0) {
    //     fprintf(stderr, "채점 오류\n");
    //     exit(1);
    // }
    // printf("채점 결과: %s\n", resultStr[GradeResult]);

    return 0;
}