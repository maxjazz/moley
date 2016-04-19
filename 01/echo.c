#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

  char c;
  while ((c = getchar()) != EOF )
    putchar(c);

  exit(0);
}
