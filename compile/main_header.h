#ifndef __MAIN_HEADER__
#define __MAIN_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char home_directory[PATH_MAXLEN];
char compile_directory[PATH_MAXLEN];
char test_directory[PATH_MAXLEN];
char result_directory[PATH_MAXLEN];

char lang_type[] = {"c", "cpp", "java", "py"};

void init(void) {
    chdir("..");
    getcwd(home_directory, PATH_MAXLEN);
    strcat(home_directory, "/");
    strcat(strcpy(compile_directory, home_directory), "compile/");
    strcat(strcpy(test_directory, home_directory), "test/");
    strcat(strcpy(result_directory, home_directory), "result/");
}

#endif // __MAIN_HEADER__