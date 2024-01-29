#include "grade.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

char *GetLanguageType(int lang) {
    char *languageType[] = {"c", "cpp", "java", "py"};
    return languageType[lang];
}

// 언어 형식에 맞게 컴파일을 진행하고 compile/code/compile_result.txt 파일에 컴파일 결과를 쓰는 함수
// 성공 시 0, 실패 시 1을 반환
int Compile(void) {
    char *compiler[] = {"gcc", "g++", "java", "python3"};
    char *compilerPath[] = {"/usr/bin/gcc", "/usr/bin/g++", "java", "/usr/bin/python3"};

    // 컴파일을 위해 소스코드 open
    int fd_source;
    char sourcePath[PATH_MAXLEN];
    sprintf(sourcePath, "%s/code/source.%s", GetCompilePath(), GetLanguageType(language));
    if ((fd_source = open(sourcePath, O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", sourcePath);
        exit(1);
    }

    // execv()를 위해 argument vector 설정
    char **args;
    char programPath[PATH_MAXLEN];
    sprintf(programPath, "%s/code/prog", GetCompilePath());
    if (language == 0) { // c
        char *compileArgs[] = {compiler[language], sourcePath, "-o", programPath, "-Wall", "-lm", "-std=gnu99", NULL};
        args = compileArgs;
    }
    else if (language == 1) { // cpp
        char *compileArgs[] = {compiler[language], sourcePath, "-o", programPath, "-Wall", "-lm", "-std=gnu++17", NULL};
        args = compileArgs;
    }
    else if (language == 2) { // java
    }
    else if (language == 3) { // python
    }

    int fd_compile_result;
    char compileResultPath[PATH_MAXLEN];
    sprintf(compileResultPath, "%s/code/compile_result.txt", GetCompilePath());
    if ((fd_compile_result = open(compileResultPath, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        fprintf(stderr, "create error for %s\n", compileResultPath);
        close(fd_source);
        return 1;
    }

    // 기존 stderr를 복사해두고, compile_result.txt 파일을 stderr로 변경
    int originalStderr = dup(STDERR_FILENO);
    dup2(fd_compile_result, STDERR_FILENO);

    // 프로세스 생성 후 execv()
    pid_t pid;
    int status;
    if ((pid = fork()) < 0) {
        fprintf(fdopen(originalStderr, "w"), "fork error in Compile()\n");
        return 1;
    }
    else if (pid == 0) {
        if (execv(compilerPath[language], args) < 0) {
            dup2(originalStderr, STDERR_FILENO);
            fprintf(stderr, "execv error\n");
            close(fd_source);
            close(fd_compile_result);
            return 1;
        }
    }
    else {
        wait(&status);
    }
    
    // stderr를 기존 값으로 돌려놓음
    dup2(originalStderr, STDERR_FILENO);

    close(fd_source);
    close(fd_compile_result);
    return 0;
}

// compile/code/compile_result.txt 파일을 읽고 컴파일 에러가 발생했는지 검사하는 함수
// 컴파일 에러가 없다면 0, 있다면 1, 함수 호출 에러 발생 시 2를 반환
int IsCompileError(void) {
    char compileResultPath[PATH_MAXLEN];
    sprintf(compileResultPath, "%s/code/compile_result.txt", GetCompilePath());
    FILE *fp_compile_result;
    if ((fp_compile_result = fopen(compileResultPath, "r")) == NULL) {
        fprintf(stderr, "fopen error for %s\n", compileResultPath);
        return 2;
    }

    char buf[BUFFER_SIZE];
    char *errorStr = "error";
    while (fgets(buf, sizeof(buf), fp_compile_result) != NULL) {
        if (strstr(buf, errorStr) != NULL) {
            fclose(fp_compile_result);
            return 1;
        }
    }

    fclose(fp_compile_result);
    return 0;
}

// compile/code/prog 프로그램을 실행하는 함수
// 런타임 에러가 없다면 0, 있다면 1, 함수 호출 에러 발생 시 2를 반환
int ExecProgram(void) {
    return 0;
}

int Grade(void) {
}