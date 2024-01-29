#ifndef __FUNC_H__
#define __FUNC_H__

#define PATH_MAXLEN 128

// init.c
extern void InitPath(void);
extern char *GetHomePath(void);
extern char *GetWorkPath(void);
extern char *GetCompilePath(void);
extern char *GetTestPath(void);
extern char *GetResultPath(void);
extern int ParseInitFile(void);

// grade.c
extern int Compile(void);
extern int IsCompileError(void);
extern int Grade(void);

extern int problemNumber; // 문제 고유 번호
extern int submitNumber;  // 제출 번호
extern int language;      // 제출 언어
extern int timeLimit;     // 시간 제한
extern int memLimit;      // 메모리 제한

#endif
