#ifndef __FUNC_H__
#define __FUNC_H__

// init.c
extern void InitPath(void);
extern char *GetHomePath(void);
extern char *GetWorkPath(void);
extern char *GetCompilePath(void);
extern char *GetTestPath(void);
extern char *GetResultPath(void);
extern void ParseInitFile(void);

// grade.c
extern int Compile(void);
extern int Grade(void);

#endif
