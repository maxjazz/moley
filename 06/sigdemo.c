#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define COUNTDOWN 100

int main(int argc, char *argv[])
{
  void f(int);
  int i;
  signal(SIGINT,f);
  for (i=0; i <= COUNTDOWN; i++)
  {
    printf("Countdown: %d\n", COUNTDOWN-i);
    sleep(1);
  }

}
void f(int signum)
{
  printf("OUCH\n");
}
