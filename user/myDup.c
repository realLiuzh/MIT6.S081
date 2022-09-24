#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{
  int fd=dup(1);
  write(fd,"hello ",6);
  write(1,"world\n",6);
  exit(0);
}
