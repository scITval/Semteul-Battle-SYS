#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void) {
    // 기존 파일들 삭제
    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error in main()\n");
        exit(1);
    }
    else if (pid == 0) {
        execl("/home/seongmo/semteul_project/compile/remove", "/home/seongmo/semteul_project/compile/remove", (char *)NULL);
    }
    else {
        wait(0);
    }

    // init.c - 디렉토리 경로 초기화
    InitPath();

    // init.c - code/compile/init.txt 파일 내용 읽기
    if (ParseInitFile() == 1) {
        fprintf(stderr, "ParseInitFile() error in init.c\n");
        exit(1);
    }

    // grade.c - 컴파일 결과를 code/compile_result.txt에 씀
    if (Compile() == 1) {
        fprintf(stderr, "Compile() error in grade.c\n");
        exit(1);
    }

    // grade.c - 컴파일 에러가 발생한 경우 코드의 실행 결과로 4를 result/result_제출번호.txt 파일에 씀
    int compileResult;
    if ((compileResult = IsCompileError()) == 1) { // 컴파일 에러
        FILE *fp_result;
        char resultPath[PATH_MAXLEN];
        sprintf(resultPath, "%s/result_%d.txt", GetResultPath(), submitNumber);
        if ((fp_result = fopen(resultPath, "w")) == NULL) {
            fprintf(stderr, "create error for %s\n", resultPath);
            exit(1);
        }

        // 코드의 실행 결과로 4를 씀
        // printf("컴파일 에러 O\n");
        fprintf(fp_result, "4");

        fclose(fp_result);
        return 0;
    }
    else if (compileResult == 2) { // IsCompileError() 함수 호출 에러
        fprintf(stderr, "IsCompileError() error in grade.c\n");
        exit(1);
    }
    // printf("컴파일 에러 X\n");

    int execResult;
    if ((execResult = ExecProgram()) == 1) { //런타임 에러
        // printf("런타임 에러 O\n");
        return 0;
    }
    else if (execResult == 2) { // ExecProgram() 함수 호출 에러
        fprintf(stderr, "execProgram() error in grade.c\n");
        exit(1);
    }
    else if (execResult == 3) { // 시간 초과
        FILE *fp_result;
        char resultPath[PATH_MAXLEN];
        sprintf(resultPath, "%s/result_%d.txt", GetResultPath(), submitNumber);
        if ((fp_result = fopen(resultPath, "w")) == NULL) {
            fprintf(stderr, "create error for %s\n", resultPath);
            exit(1);
        }

        // 코드의 실행 결과로 2를 씀
        fprintf(fp_result, "2");
        // printf("시간 초과\n");

        fclose(fp_result);
        return 0;
    }
    else if (execResult == 4) { // 메모리 초과
        FILE *fp_result;
        char resultPath[PATH_MAXLEN];
        sprintf(resultPath, "%s/result_%d.txt", GetResultPath(), submitNumber);
        if ((fp_result = fopen(resultPath, "w")) == NULL) {
            fprintf(stderr, "create error for %s\n", resultPath);
            exit(1);
        }

        // 코드의 실행 결과로 3를 씀
        fprintf(fp_result, "3");
        // printf("메모리 초과\n");

        fclose(fp_result);
        return 0;
    }
    // printf("런타임 에러 X\n");

    return 0;
}