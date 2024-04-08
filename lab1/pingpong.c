#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h> // 需要包含头文件来使用 NULL

#define Message 16 // 定义 Message 不应该有分号

char *mesg = "hello xv6";

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        fprintf(2, "have argument\n");
        exit(1);
    }

    int p[2]; // 管道的文件描述符对
    char inbuf[Message]; // 接收数组
    int pid;
    int nbytes;
    int i = pipe(p);
    if (i < 0) {
        fprintf(2, "pipe error");
        exit(1);
    }
    // -------------------------------------
    pid = fork();
    if (pid > 0) {
        write(p[1], mesg, Message);
        close(p[1]);
        wait(NULL);
        nbytes = read(p[0], inbuf, Message);
        if (nbytes < 0) {
            exit(1);
        }
        printf("%d: received pong\n",getpid());
        close(p[0]);
        exit(0);

    }
    else // 正确拼写为 else
    {
        nbytes = read(p[0], inbuf, Message);
        if (nbytes < 0) {
            exit(1);
        }
        printf("%d: received ping\n",getpid());
        close(p[0]);
        write(p[1], mesg, Message);
        close(p[1]);
        exit(0);
    }
}
