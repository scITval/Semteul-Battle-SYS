#include "init.h"

#include <unistd.h>
#include <stdio.h>

void init(void) {
    getcwd(compile_directory, PATH_MAXLEN);
    printf("%s\n", compile_directory);
}