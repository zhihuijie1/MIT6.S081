#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

void process(int pid, int p[2]);
int *prime(int primes[]);

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        fprintf(2, "argument error");
        exit(1);
    }

    // 开启管道
    int pp[2];
    int k = pipe(pp);
    if (k < 0) {
        exit(1);
    }

    // fork
    int ppid = fork();

    // 传入数组
    if (ppid > 0) {
        int primes[33];
        for (int i = 0; i < 33; i++) {
            primes[i] = i + 2;
        }

        // 写入数据到管道
        for (int i = 0; i < 33; i++) {
            write(pp[1], &primes[i], sizeof(int));
        }

        // 调用递归函数
        process(-1, pp);

        // 等待子进程结束
        wait(NULL);

        // 关闭写端
        close(pp[1]);
    }
    return 0;
}

// 递归函数
void process(int pid, int p[2]) {
    if (pid < 0) {
        int inbuf[33];
        // 1:读取数据
        for (int i = 0; i < 33; i++) {
            read(p[0], &inbuf[i], sizeof(int));
        }
        close(p[0]);

        // 2：打印素数，并筛选出新数，返回存储新数的数组
        int *next = prime(inbuf);

        // 3:开启管道
        int pp[2];
        int k = pipe(pp);
        if (k < 0) {
            exit(1);
        }

        // 4:fork
        int ppid = fork();

        // 5:写入next数组
        if (ppid > 0) {
            int *ptr = next;
            while (*ptr != -1) {
                int value = *ptr;
                write(pp[1], &value, sizeof(int));
                ptr++;
            }
        }

        // 7:关闭write
        close(pp[1]);

        // 6:循环递归
        process(-1, pp);
    }
}

// 打印素数 并返回过滤后的数组
int *prime(int primes[]) {
    int p = primes[0];

    printf("prime:%d\n", p); // 素数

    int count = 0;

    for (int i = 1; i < 33; i++) {
        if (primes[i] == 0 || primes[i] % p == 0) {
            // 不可以放在通往下一站的列车上
            primes[i] = -1;
            continue;
        }

        count++; // 记录一下有几个可以乘坐通往下一站的列车
    }

    // 准备列车
    int *nextPrimes = malloc(count * sizeof(int) + 1);
    if (nextPrimes == NULL) {
        fprintf(2, "Memory allocation failed");
        exit(1);
    }

    // 上车
    int index = 0;
    for (int i = 1; i < 33; i++) {
        if (primes[i] != -1) {
            nextPrimes[index++] = primes[i];
        }
    }
    nextPrimes[index] = -1; // 标记数组结束

    return nextPrimes;
}
