#ifndef __INIT_H__
#define __INIT_H__

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char home_directory[PATH_MAXLEN];
char compile_directory[PATH_MAXLEN];
char test_directory[PATH_MAXLEN];
char result_directory[PATH_MAXLEN];

extern int problemNumber; // 문제 고유 번호
extern int submitNumber;  // 제출 번호
extern char language[30];      // 제출 언어
// extern char *language;      // 제출 언어
extern int timeLimit;     // 시간 제한
extern int memLimit;      // 메모리 제한

void init_directory(void);
char *get_home_directory(void);
char *get_compile_directory(void);
char *get_test_directory(void);
char *get_result_directory(void);

void parse_init_file(void);

#endif // __INIT_H__