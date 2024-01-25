#include "init.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 절대 경로들을 초기화하는 함수
void InitPath(void) {
    sprintf(homePath, "%s", getenv("HOME"));
    sprintf(workPath, "%s/semteul_project", GetHomePath());
    sprintf(compilePath, "%s/compile", GetWorkPath());
    sprintf(testPath, "%s/test", GetWorkPath());
    sprintf(resultPath, "%s/result", GetWorkPath());
}
// 절대 경로를 반환하는 함수들
char *GetHomePath(void) { return homePath; }
char *GetWorkPath(void) { return workPath; }
char *GetCompilePath(void) { return compilePath; }
char *GetTestPath(void) { return testPath; }
char *GetResultPath(void) { return resultPath; }

// compile/code/init.txt 파일에서 정보들을 정리하는 함수
// 성공 시 0, 실패 시 1을 반환
int ParseInitFile(void) {
    int fd_init; // init.txt 파일 디스크립터
    char init_txt_path[PATH_MAXLEN]; // init.txt 절대 경로
    sprintf(init_txt_path, "%s/code/init.txt", GetCompilePath());
    if ((fd_init = open(init_txt_path, O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", init_txt_path);
        close(fd_init);
        return 1;
    }

    char buf[BUFFER_SIZE];
    char temp[1];
    ssize_t len;
    int idx = 0, cnt = 0;
    int info[5];
    // 개행 문자를 기준으로 5줄은 정수 값으로 입력받은 후 각 정보를 grade.c에서 사용할 변수에 저장
    while ((len = read(fd_init, temp, 1)) > 0) {
        if (temp[0] == '\n') {
            buf[idx] = 0;
            info[cnt] = atoi(buf);
            memset(buf, 0, BUFFER_SIZE);
            idx = 0;
            cnt++;
        }
        if (cnt == 5) {
            break;
        }
        buf[idx++] = temp[0];
    }
    problemNumber = info[0];
    submitNumber = info[1];
    language = info[2];
    timeLimit = info[3];
    memLimit = info[4];
    
    int fd_source; // source.파일형식 파일 디스크립터
    char source_path[PATH_MAXLEN]; // source.파일형식 절대 경로
    sprintf(source_path, "%s/code/source.%s", GetCompilePath(), languageType[language]);
    // source.파일형식 소스파일을 644권한으로 생성
    if ((fd_source = open(source_path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        fprintf(stderr, "create error for %s\n", source_path);
        close(fd_init);
        close(fd_source);
        return 1;
    }

    // init.txt에 남은 부분(코드)을 source.파일형식 소스파일에 복사
    while ((len = read(fd_init, buf, BUFFER_SIZE)) > 0) {
        if (len < 0) {
            fprintf(stderr, "read error for %s\n", init_txt_path);
            close(fd_init);
            close(fd_source);
            return 1;
        }
        else if (len == 0) {
            break;
        }
        else {
            if (len != write(fd_source, buf, len)) {
                fprintf(stderr, "write error for %s\n", source_path);
                close(fd_init);
                close(fd_source);
                return 1;
            }
        }
    }

    close(fd_init);
    close(fd_source);
    return 0;
}