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
