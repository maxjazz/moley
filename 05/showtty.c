#include <stdio.h>
#include <termios.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
  struct termios ttyinfo;
  if (tcgetattr(0,&ttyinfo) == -1)
  {
    perror ("tcgetattr");
    exit(1);
  }

  showbaud(cfgetospeed(&ttyinfo));

  printf ("The erase character is ASCII %d, Ctrl-%c\n",
            ttyinfo.c_cc[VERASE],
            ttyinfo.c_cc[VERASE]-1+'A');

  printf ("The line kill character is ASCII %d, Ctrl-%c\n",
            ttyinfo.c_cc[VKILL],
            ttyinfo.c_cc[VKILL]-1+'A');

  show_some_flags(&ttyinfo);
}

showbaud(int speed)
{
  printf("The baud rate is");
  switch (speed)
  {
    case B300: printf ("300");
    case B600: printf ("600");
    case B1200: printf ("1200");
    case B1800: printf ("1800");
    case B2400: printf ("2400");
    case B4800: printf ("4800");
    case B9600: printf ("9600");
    default: ;
  }
}

struct flaginfo
{
  int fl_value;
  char *fl_name;
};

struct flaginfo input_flags[]=
{
  IGNBRK,
  BRKINT,
  IGNPAR,
  PARMRK,
  INPCK,
  ISTRIP,
  INLCR,
  IGNCR,
  ICRNL,
  IXON,
  IXOFF,
  0,
  NULL
};

struct flaginfo local_flags[]=
{
  ISIG, "Enables signals",
  ICANON, "Canonical input",
  ECHO, "Enable echo",
  ECHOE, "Echo ERASE",
  ECHOK, "Echo KILL",
  0, NULL
};

void show_some_flags (struct termios *ttyp)
{
  show_flagset(ttyp->c_iflag, input_flags);
  show_flagset(ttyp->c_lflag, input_flags);
}

show_flagset (int value, struct flaginfo bitnames[])
{
  int i;
  for (i=0; bitnames[i].fl_value; i++)
  {
    printf ("%s is: ", bitnames[i].fl_name);
    if (value & bitnames[i].fl_value)
      printf("ON\n");
    else
      printf("OFF\n");
  }
}
