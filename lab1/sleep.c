#include <unistd.h>
#include <stdlib.h>
#include <strsafe.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(2, "argument  error");
        exit(1);
    }
    //两个参数
    sleep(atoi(argv[1]));
    exit(0);
}

/**
 * 命令行参数调用时写法如上所示
 * argc -> 参数的数量
 * argv[] -> 存储参数
 * argv[0] -> 函数名
 * argv[1] -> 第一个参数
 * argv[2] -> 第二个参数
 * .......
 *
 * 当只有一个参数时 argc == 2
 * 一个是函数名，一个是参数
*/