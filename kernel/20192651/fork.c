#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

int fork_main() {
    pid_t pid;
    /* 자식 프로세스를 생성합니다. */
    pid = fork(); // pid(p) > 0: 자식 프로세스의 pid; pid(c) == 0

    if (pid < 0) {
        /* 에러가 발생했습니다. 여기서부터 자식 프로세스가 시작됩니다. */
        fprintf(stderr, "포크 실패");
        return 1;
    } else if (pid == 0) {
        /* 자식 프로세스 */
        printf("자식 프로세스의 PID: %d\n", getpid());;
        execlp("/bin/ls", "ls", NULL); // 자식 ≠ 부모 이제
    } else {
        /* 부모 프로세스 */
        /* 부모는 자식이 완료될 때까지 기다립니다. */
        wait(NULL); // 대기 상태로 전환
        printf("자식 완료");
        printf("부모 프로세스의 PID: %d\n", getpid());;
    }
    return 0;
}
