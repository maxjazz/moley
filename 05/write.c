#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 512

int main (int argc, char *argv[])
{
  int fd;
  char buf[BUFSIZE];

  if (argc != 2)
  {
    fprintf(stderr, "Usage: write <ttyname>\n");
    exit(1);
  }

  fd = open (argv[1], O_WRONLY);
  if (fd == 1)
  {
    perror(argv[1]);
    exit(1);
  }

  while (fgets(buf, BUFSIZE, stdin)!=NULL)
  {
    if (write(fd,buf,strlen(buf))==-1)
      break;
  }

  close(fd);
  exit(0);
}
