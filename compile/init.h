#ifndef __INIT_H__
#define __INIT_H__

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char home_directory[PATH_MAXLEN];
char compile_directory[PATH_MAXLEN];
char test_directory[PATH_MAXLEN];
char result_directory[PATH_MAXLEN];

char *lang_type[] = {"c", "cpp", "java", "py"};

void init_directory(void);
char *get_home_directory(void);
char *get_compile_directory(void);
char *get_test_directory(void);
char *get_result_directory(void);

#endif // __INIT_H__