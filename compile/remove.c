#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

void deleteFilesInDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // 디렉토리 열기
    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // 디렉토리 내의 파일 순회
    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리(.)나 상위 디렉토리(..)는 무시
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, "init.txt")) {
            continue;
        }

        // 파일 경로 생성
        char filePath[1024];
        strcpy(filePath, path);
        strcat(filePath, "/");
        strcat(filePath, entry->d_name);

        // 파일 삭제
        if (remove(filePath) != 0) {
            perror("Error deleting file");
        } else {
            printf("Deleted: %s\n", filePath);
        }
    }

    closedir(dir);
}

int main() {
    char *resultPath = "../result";
    char *codePath = "../compile/code";
    deleteFilesInDirectory(resultPath);
    deleteFilesInDirectory(codePath);
}