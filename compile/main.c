#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    InitPath(); // init.c - 디렉토리 경로 초기화
    ParseInitFile(); // init.c - init.txt 파일 내용 읽기
    // printf("문제 번호: %d\n제출 번호: %d\n제출 언어: %s\n시간 제한: %d\n메모리 제한: %d\n", problemNumber, submitNumber, language, timeLimit, memLimit);
    // int GradeResult;
    // char *resultStr[] = {"틀림", "맞음", "시간 초과", "메모리 초과", "컴파일 에러", "런타임 에러"};
    // if ((GradeResult = Compile()) < 0) {
    //     fprintf(stderr, "채점 오류\n");
    //     exit(1);
    // }
    // printf("채점 결과: %s\n", resultStr[GradeResult]);

    return 0;
}