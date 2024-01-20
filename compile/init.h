#ifndef __INIT_H__
#define __INIT_H__

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char compile_directory[PATH_MAXLEN];

char *lang_type[] = {"c", "cpp", "java", "py"};

void init(void);
char *get_compile_directory();

#endif // __INIT_H__