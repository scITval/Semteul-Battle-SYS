#ifndef __MAIN_HEADER__
#define __MAIN_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char compile_directory[PATH_MAXLEN];

char lang_type[] = {"c", "cpp", "java", "py"};

void init(void) {
    getcwd(compile_directory, PATH_MAXLEN);
}

#endif // __MAIN_HEADER__