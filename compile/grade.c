#include "grade.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

char *GetLanguageType(int lang) {
    char *languageType[] = {"c", "cpp", "java", "py"};
    return languageType[lang];
}

int Compile(void) {
    char *compiler[] = {"gcc", "g++", "java", "python3"};
    char *compilerPATH[] = {"/usr/bin/gcc", "/usr/bin/g++", "java", "/usr/bin/python3"};

    int fd_source;
    char sourcePATH[PATH_MAXLEN];
    sprintf(sourcePATH, "%s/code/source.%s", GetCompilePath(), GetLanguageType(language));
    if ((fd_source = open(sourcePATH, O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", sourcePATH);
        exit(1);
    }

    char **args;
    if (language == 0) { // c
        char *temp[] = {compiler[language], sourcePATH, "-o", "/home/seongmo/semteul_project/compile/code/prog", NULL};
        args = temp;
    }
    else if (language == 1) { // cpp
        char *temp[] = {compiler[language], sourcePATH, "-o", "/home/seongmo/semteul_project/compile/code/prog", NULL};
        args = temp;
    }
    else if (language == 2) { // java
    }
    else if (language == 3) { // python
        char *temp[] = {compiler[language], sourcePATH, NULL};
        args = temp;
    }

    pid_t pid;
    if ((pid = fork()) == 0) {
        if (execv(compilerPATH[language], args) < 0) {
            fprintf(stderr, "execv error\n");
            exit(1);
        }
        remove(sourcePATH);
    }

    close(fd_source);
    return 0;
}

int Grade(void) {
}