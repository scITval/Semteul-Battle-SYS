#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    // InitDirectory();
    // ParseInitFile();
    // printf("문제 번호: %d\n제출 번호: %d\n제출 언어: %s\n시간 제한: %d\n메모리 제한: %d\n", problemNumber, submitNumber, language, timeLimit, memLimit);
    int GradeResult;
    if ((GradeResult = Grade()) == 0) { // 틀렸습니다.
        printf("틀렸습니다.\n");
    }
    else if (GradeResult == 1) { // 맞았습니다.
        printf("맞았습니다.\n");
    }
    else if (GradeResult == 2) { // 시간 초과
        printf("시간 초과\n");
    }
    else if (GradeResult == 3) { // 메모리 초과
        printf("메모리 초과\n");
    }
    else if (GradeResult == 4) { // 컴파일 에러
        printf("컴파일 에러\n");
    }
    else { // 런타임 에러
        printf("런타임 에러\n");
    }

    return 0;
}