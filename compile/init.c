#include "init.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void InitPath(void) {
    sprintf(homePath, "%s", getenv("HOME"));
    sprintf(workPath, "%s/semteul_project", GetHomePath());
    sprintf(compilePath, "%s/compile", GetWorkPath());
    sprintf(testPath, "%s/test", GetWorkPath());
    sprintf(resultPath, "%s/result", GetWorkPath());
}
char *GetHomePath(void) { return homePath; }
char *GetWorkPath(void) { return workPath; }
char *GetCompilePath(void) { return compilePath; }
char *GetTestPath(void) { return testPath; }
char *GetResultPath(void) { return resultPath; }

int ParseInitFile(void) {
    int fd_init;
    char init_txt_path[PATH_MAXLEN];
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
    
    int fd_source;
    char source_path[PATH_MAXLEN];
    sprintf(source_path, "%s/code/source.%s", GetCompilePath(), languageType[language]);
    if ((fd_source = open(source_path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        fprintf(stderr, "create error for %s\n", source_path);
        close(fd_init);
        close(fd_source);
        return 1;
    }

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