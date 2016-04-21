/*
 cp <source> <destination>

*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops (char *, char *);

int main(int argc, char *argv[])
{
  int srcfd, dstfd, n_chars;
  char buf[BUFFERSIZE];

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <source> <destination> \n", *argv );
    exit(1);
  }

  if ((srcfd = open(argv[1], O_RDONLY)) == -1)
    oops ("Can not open", argv[1]);

  if ((dstfd = creat(argv[2], COPYMODE)) == -1)
    oops ("Can not creat", argv[2]);

  while (( n_chars = read(srcfd, buf, BUFFERSIZE)) > 0)
    if (write (dstfd, buf, n_chars) != n_chars )
      oops("Write error to", argv[2]);

  if (n_chars == -1)
    oops("Read error from", argv[1]);

  if (close(srcfd) == -1 || close(dstfd) == -1)
    oops ("Error closing files", "");
}

void oops (char *s1, char *s2)
  {
    fprintf(stderr, "Error: %s\n", s1);
    perror (s2);
    exit(1);

  }
