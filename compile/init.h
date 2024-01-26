#ifndef __INIT_H__
#define __INIT_H__

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

char homePath[PATH_MAXLEN];
char workPath[PATH_MAXLEN];
char compilePath[PATH_MAXLEN];
char testPath[PATH_MAXLEN];
char resultPath[PATH_MAXLEN];

// grade.h
extern int problemNumber; // 문제 고유 번호
extern int submitNumber;  // 제출 번호
extern int language;      // 제출 언어
extern int timeLimit;     // 시간 제한
extern int memLimit;      // 메모리 제한
extern char *GetLanguageType(int);

void InitPath(void);
char *GetHomePath(void);
char *GetWorkPath(void);
char *GetCompilePath(void);
char *GetTestPath(void);
char *GetResultPath(void);

int ParseInitFile(void);

#endif // __INIT_H__