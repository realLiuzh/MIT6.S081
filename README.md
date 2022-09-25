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

## pingpong

pingpong.c

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {

    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);

    char buf[1];

    if (fork() == 0) {
        close(p1[1]);    //关闭管道写的方向
        read(p1[0], buf, 1);
        close(p1[0]);
        fprintf(1, "%d: received ping\n", getpid());

        close(p2[0]);
        write(p2[1], "2", 1);
        close(p2[1]);
        exit(0);
    } else {
        close(p1[0]); //关闭管道读的方向
        write(p1[1], "1", 1);
        close(p1[1]);

        close(p2[1]);
        read(p2[0], buf, 1);
        close(p2[0]);
        fprintf(1, "%d: received pong\n", getpid());
        exit(0);
    }
}
```

