#include "init.h"

#include <stdio.h>
#include <string.h>
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

void ParseInitFile(void) {
    int fd_init;
    char init_txt_path[PATH_MAXLEN];
    sprintf(init_txt_path, "%s/code/init.txt", GetCompilePath());
    if ((fd_init = open(init_txt_path, O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", init_txt_path);
        exit(1);
    }

    char buf[BUFFER_SIZE];

    close(fd_init);
}