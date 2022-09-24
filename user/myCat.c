#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// myCat.c
// 标准输入与输出的demo
int
main(int argc,char *argv[]){
	char buf[512];
	int n,m;

	while(1){
	 n=read(0,buf,sizeof buf);
	 if(n==0){
	   break;
	 }
	 if(n<0){
	   fprintf(2,"read error/n");
	   exit(1);
	 }
	 m=write(1,buf,n);
	 if(n!=m){
	   fprintf(2,"write error/n");
	   exit(1);
	 }
	}	
       return 0;	
}

