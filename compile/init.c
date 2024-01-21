#include "init.h"

#include <unistd.h>
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