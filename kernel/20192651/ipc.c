#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int ipc_week6(void) 
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];  // 프로세스의 주소 (like 메모리 주소 포인터)
    pid_t pid;

    // 파이프 생성
    if (pipe(fd) == -1) { 
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // 자식 프로세스 생성
    pid = fork();  

    if (pid < 0) {
        // 에러 발생
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid > 0) {  // 자식 생성되면 여기로 옴 
        // 부모 프로세스
        close(fd[READ_END]); // 사용되지 않는 파이프의 끝을 닫음
        // 파이프에 쓰기
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        // 파이프의 쓰기 끝을 닫음
        close(fd[WRITE_END]);
    } else {
        // 자식 프로세스
        close(fd[WRITE_END]); // 사용되지 않는 파이프의 끝을 닫음
        // 파이프에서 읽기
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("read: %s", read_msg);
        // 파이프의 읽기 끝을 닫음
        close(fd[READ_END]);
    }
    return 0;
}