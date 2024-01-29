#ifndef __GRADE_H__
#define __GRADE_H__

#define BUFFER_SIZE 1024
#define PATH_MAXLEN 128

int problemNumber; // 문제 고유 번호
int submitNumber;  // 제출 번호
int language;      // 제출 언어
int timeLimit;     // 시간 제한
int memLimit;      // 메모리 제한

int Compile(void);
int IsCompileError(void);
int ExecProgram(void);
int Grade(void);
char *GetLanguageType(int);

// init.c
extern char *GetCompilePath(void);

#endif // __GRADE_H__