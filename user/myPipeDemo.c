#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{
   char* array[2];
   array[0]="wc";
   array[1]=0;

   // 创建管道。管道实际上是一对文件描述符
   int p[2];
   pipe(p);

   int pid=fork();
   if(pid==0){
     close(0);	//关闭0号fd
     dup(p[0]);	//p[0] pipe的读取端获得0号文件描述符
     close(p[0]);
     close(p[1]);
     exec("wc",array);
   }else{
     close(p[0]);
     write(p[1],"hello world\n",12);
     close(p[1]);
   }
}
