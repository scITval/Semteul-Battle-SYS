#include "grade.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

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
        close(fd_source);
        close(fd_compile_result);
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
        exit(0);
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
// 런타임 에러가 없다면 0, 있다면 1, 함수 호출 에러 발생 시 2
// 실행 중에 시간 초과가 발생한 경우 3, 메모리 초과가 발생한 경우 4를 반환
int ExecProgram(void) {
    DIR *dir;
    struct dirent *entry;
    char inputPath[PATH_MAXLEN];
    sprintf(inputPath, "%s/input/%d", GetTestPath(), problemNumber);
    // test/input/문제번호 디렉토리 열기
    if ((dir = opendir(inputPath)) == NULL) {
        fprintf(stderr, "opendir error for %s\n", inputPath);
        return 2;
    }

    // 표준 입출력 기존 값 복사
    int originalStdin = dup(STDIN_FILENO);
    int originalStdout = dup(STDOUT_FILENO);

    // 디렉토리 내의 파일 순회
    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리(.)나 상위 디렉토리(..)는 무시
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }

        // 파일 경로 생성
        char testCasePath[PATH_MAXLEN];
        strcpy(testCasePath, inputPath);
        strcat(testCasePath, "/");
        strcat(testCasePath, entry->d_name);

        struct timeval start;
        gettimeofday(&start, NULL);
        long timeLimitMicros = timeLimit * CLOCKS_PER_SEC;

        pid_t pid;
        int status;
        if ((pid = fork()) < 0) {
            fprintf(stderr, "fork error in ExecProgram()\n");
            closedir(dir);
            return 2;
        }
        // 자식 프로세스
        // 사용자 프로그램 실행
        else if (pid == 0) { 
            // 테스트 케이스의 입력 값
            int fd_input;
            if ((fd_input = open(testCasePath, O_RDONLY)) < 0) {
                fprintf(stderr, "open error for %s\n", testCasePath);
                closedir(dir);
                return 2;
            }

            // 프로그램의 실행 결과를 해당 경로에 씀
            int fd_result;
            char resultPath[PATH_MAXLEN];
            strcpy(resultPath, GetResultPath());
            strcat(resultPath, "/");
            strcat(resultPath, entry->d_name);
            if ((fd_result = open(resultPath, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
                fprintf(stderr, "open error for %s\n", resultPath);
                closedir(dir);
                close(fd_input);
                return 2;
            }

            // 표준 입출력을 파일로 변경
            dup2(fd_input, STDIN_FILENO);
            dup2(fd_result, STDOUT_FILENO);

            // 사용자 프로그램 실행
            char programPath[PATH_MAXLEN];
            sprintf(programPath, "%s/code/prog", GetCompilePath());
            char *programArgs[] = {programPath, NULL};
            execv(programPath, programArgs);

            close(fd_input);
            close(fd_result);
            exit(0);
        }
        // 부모 프로세스
        // 사용자 프로그램의 시간 초과를 검사
        else {
            struct timeval mid;
            long seconds, micros;
            int status;
            // 자식 프로세스가 정상 종료되거나 강제 종료될 때까지 반복
            while (1) {
                // 계속해서 경과 시간 체크
                gettimeofday(&mid, NULL);
                seconds = mid.tv_sec - start.tv_sec;
                micros = (seconds * CLOCKS_PER_SEC) + mid.tv_usec - start.tv_usec;

                // 마이크로초 단위로 시간 초과를 검사
                // 시간 초과 발생한 경우
                if (micros > timeLimit * CLOCKS_PER_SEC) {
                    kill(pid, SIGKILL);
                    fprintf(fdopen(originalStdout, "w"), "강제 종료, 종료시간: %ld 마이크로초\n", micros);

                    // 표준 입출력을 기존 값으로 돌려놓음
                    dup2(originalStdin, STDIN_FILENO);
                    dup2(originalStdout, STDOUT_FILENO);

                    closedir(dir);
                    return 3;
                }

                // 자식 프로세스의 상태를 확인
                pid_t isTerminatedPid = waitpid(pid, &status, WNOHANG);

                // 자식 프로세스가 종료된 경우
                if (isTerminatedPid > 0) {

                    // 자식 프로세스가 정상 종료된 경우
                    if (WIFEXITED(status)) {
                        fprintf(fdopen(originalStdout, "w"), "정상 종료, 종료시간: %ld 마이크로초\n", micros);
                        break;
                        // 정상 종료시 추가적인 작업 수행 가능
                    }
                    // 자식 프로세스가 강제 종료된 경우(시간 초과)
                    else if (WIFSIGNALED(status)) {
                        fprintf(fdopen(originalStdout, "w"), "강제 종료, 종료시간: %ld 마이크로초\n", micros);

                        // 표준 입출력을 기존 값으로 돌려놓음
                        dup2(originalStdin, STDIN_FILENO);
                        dup2(originalStdout, STDOUT_FILENO);

                        closedir(dir);
                        return 3;
                    }                
                }
            }

            // 시간 초과 발생하지 않은 경우
            // if (WIFEXITED(status)) {
                // fprintf(fdopen(originalStdout, "w"), "자식 프로세스 정상 종료\n\n");
            // }
        }
    }

    // 표준 입출력을 기존 값으로 돌려놓음
    dup2(originalStdin, STDIN_FILENO);
    dup2(originalStdout, STDOUT_FILENO);

    closedir(dir);
    return 0;
}

int Grade(void) {
    return 0;
}
