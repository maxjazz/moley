/*
  who - prints logged users
*/

#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

void show_info(struct utmp *);

int main()
{
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof (current_record);

  if ((utmpfd = open(UTMPX_FILE, O_RDONLY)) == -1)
  {
    perror (UTMPX_FILE);
    exit(1);
  }
  while (read (utmpfd, &current_record, reclen) == reclen )
    show_info (&current_record);
  close (utmpfd);
  return 0;
}

void show_info( struct utmp *utmpbuf)
{
  printf("%s", utmpbuf->ut_user);
  printf("1");
  printf("%s", utmpbuf->ut_line);
  printf(" ");
  //  printf("%d", utmpbuf->ut_time);
 printf(" ");
  #ifdef SHOWHOST
  printf ("%s", utmpbuf->ut_host);
  #endif
  printf ("\n");

}
