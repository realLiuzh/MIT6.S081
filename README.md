# Lab1

## sleep

sleep.c

```c
//1.获取用户输入的命令行参数
//2.调用 sleep() System call
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    int i, len;
    // 参数校验
    if (argc != 2) {
        write(1, "input error!\n\0", 14);
        exit(1);
    }
    char *timeStr = argv[1];
    char *temp = timeStr;
    for (i = 0, len = strlen(timeStr); i < len; i++) {
        if ('0' <= *(temp + i) && *(temp + i) <= '9')
            continue;
        else {
            write(1, "input error!\n\0", 14);
            exit(0);
        }
    }
    // 系统调用
    int time = atoi(timeStr);
    sleep(time);
    exit(0);
}

```

