#ifndef __INIT_H__
#define __INIT_H__

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char homePATH[PATH_MAXLEN];
char compilePATH[PATH_MAXLEN];
char testPATH[PATH_MAXLEN];
char resultPATH[PATH_MAXLEN];

extern int problemNumber; // 문제 고유 번호
extern int submitNumber;  // 제출 번호
extern char language[30];      // 제출 언어
// extern char *language;      // 제출 언어
extern int timeLimit;     // 시간 제한
extern int memLimit;      // 메모리 제한

void InitDirectory(void);
char *GetHomeDirectory(void);
char *GetCompileDirectory(void);
char *GetTestDirectory(void);
char *GetResultDirectory(void);

void ParseInitFile(void);

#endif // __INIT_H__