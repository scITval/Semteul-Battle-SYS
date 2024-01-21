#include "init.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_directory(void) {
    strcpy(home_directory, getenv("HOME"));
    strcat(home_directory, "/");

    char work_path[PATH_MAXLEN];
    strcpy(work_path, home_directory);
    strcat(work_path, "semteul_project/");

    strcpy(compile_directory, work_path);
    strcat(compile_directory, "compile/");

    strcpy(test_directory, work_path);
    strcat(test_directory, "test/");

    strcpy(result_directory, work_path);
    strcat(result_directory, "result/");
}
char *get_home_directory(void) { return home_directory; }
char *get_compile_directory(void) { return compile_directory; }
char *get_test_directory(void) { return test_directory; }
char *get_result_directory(void) { return result_directory; }

void parse_init_file(void) {
    int fd_init;
    char init_file[PATH_MAXLEN];
    strcpy(init_file, get_compile_directory());
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

    // int fd_source;
    // char source_file[PATH_MAXLEN];
    // strcpy(source_file, get_compile_directory());
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
