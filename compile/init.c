#include "init.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitDirectory(void) {
    strcpy(homePATH, getenv("HOME"));
    strcat(homePATH, "/");

    char work_path[PATH_MAXLEN];
    strcpy(work_path, homePATH);
    strcat(work_path, "semteul_project/");

    strcpy(compilePATH, work_path);
    strcat(compilePATH, "compile/");

    strcpy(testPATH, work_path);
    strcat(testPATH, "test/");

    strcpy(resultPATH, work_path);
    strcat(resultPATH, "result/");
}
char *GetHomeDirectory(void) { return homePATH; }
char *GetCompileDirectory(void) { return compilePATH; }
char *GetTestDirectory(void) { return testPATH; }
char *GetResultDirectory(void) { return resultPATH; }

void ParseInitFile(void) {
    int fd_init;
    char init_file[PATH_MAXLEN];
    strcpy(init_file, GetCompileDirectory());
    strcat(init_file, "code/init.txt");
    if ((fd_init = open(init_file, O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", init_file);
        exit(1);
    }
    
    char temp[1];
    char buf[BUFFER_SIZE] = "";
    int cnt = 0;
    while (read(fd_init, temp, 1) > 0) {
        if (cnt == 5) break;

        if (!strcmp(temp, "\n")) {
            // printf("%ld\n", strlen(buf));
            buf[strlen(buf)] = '\0';
            if (cnt == 0) problemNumber = atoi(buf);
            else if (cnt == 1) submitNumber = atoi(buf);
            else if (cnt == 2) strcpy(language, buf);
            else if (cnt == 3) timeLimit = atoi(buf);
            else  memLimit = atoi(buf);

            strcpy(buf, "");
            cnt++;
            continue;
        }
        strcat(buf, temp);
    }
    printf("문제 번호: %d\n제출 번호: %d\n제출 언어: %s\n시간 제한: %d\n메모리 제한: %d\n", problemNumber, submitNumber, language, timeLimit, memLimit);

    int fd_source;
    char source_file[PATH_MAXLEN];
    // GetCompileDirectory();
    // strcpy(source_file, GetCompileDirectory());
    // printf("%s\n", source_file);
    // strcat(source_file, "code/source.");
    // printf("%s\n", source_file);
    // strcat(source_file, language);
    // printf("%s\n", language);

    // if ((fd_source = open("")))

    // int len;
    // while ((len = read(fd_init, buf, BUFFER_SIZE)) > 0) {
    //     if (len != write(fd_source, buf, len)) {
    //         fprintf(stderr, "write error for %s\n", source_file);
    //         exit(1);
    //     }
    // }

    close(fd_init);
}
