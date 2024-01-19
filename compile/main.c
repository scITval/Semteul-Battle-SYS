#include "main_header.h"

void file_parse(); // init.txt 파일을 파싱해서 정보들을 정리하는 함수

int problemNumber; // 문제 고유 번호
int submitNumber;  // 제출 번호
int language;      // 제출 언어
int timeLimit;     // 시간 제한
int memLimit;      // 메모리 제한

int main(void) {
    init();
    // file_parse();

    return 0;
}

// init.txt 파일을 파싱해서 정보들을 정리하는 함수
void file_parse(void) {
    // init.txt open
    int fd_init;
    char init_path[BUFFER_SIZE];
    if ((fd_init = open(init_path, O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", init_path);
        exit(1);
    }

    close(fd_init);
}