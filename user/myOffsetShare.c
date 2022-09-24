#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{

	int pid=fork();
	if(pid==0){
	  write(1,"hello ",6);
	  exit(0);
	}else{
	  wait((int* )0);
	  write(1,"world\n",6);
	}
}
