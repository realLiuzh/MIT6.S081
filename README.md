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

## find

find.c

```c
#include "kernel/types.h"

#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

void find(char *path, const char *filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot fstat %s\n", path);
    close(fd);
    return;
  }

  //参数错误，find的第一个参数必须是目录
  if (st.type != T_DIR) {
    fprintf(2, "usage: find <DIRECTORY> <filename>\n");
    return;
  }

  if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
    fprintf(2, "find: path too long\n");
    return;
  }
  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/'; //p指向最后一个'/'之后
  while (read(fd, &de, sizeof de) == sizeof de) {
    if (de.inum == 0)
      continue;
    memmove(p, de.name, DIRSIZ); //添加路径名称
    p[DIRSIZ] = 0;               //字符串结束标志
    if (stat(buf, &st) < 0) {
      fprintf(2, "find: cannot stat %s\n", buf);
      continue;
    }
    //不要在“.”和“..”目录中递归
    if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
      find(buf, filename);
    } else if (strcmp(filename, p) == 0)
      printf("%s\n", buf);
  }

  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    fprintf(2, "usage: find <directory> <filename>\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
```

