//#include <fcntl.h>
#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
   char* array[2];

   array[0]="cat";
   array[1]=0;
   if(fork()==0){
  	close(0);
   	open("wc",O_RDONLY);
   	exec("cat",array);
   }
   return 0;
}
