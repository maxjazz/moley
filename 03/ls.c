/*

ls - show directory content

*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char []);
void mode_to_letters(int, char []);

int main (int argc, char *argv[])

{
  if (argc == 1)
    do_ls(".");
  else
    while (--argc)
    {
      printf("%s\n", *++argv );
      do_ls(*argv);
    }

}

void do_ls (char dirname[])
{
  DIR *dir_ptr;
  struct dirent *direntp;
  if ((dir_ptr = opendir (dirname))==NULL)
    fprintf(stderr, "ls: cannot open %s\n", dirname);
  else
    {
      while ((direntp = readdir(dir_ptr))!=NULL)
        printf("%s\n", direntp->d_name );
    }
  closedir(dir_ptr);
}

void mode_to_letter(int mode, char str[])
{
  strcpy (str,"----------");
  if (S_ISDIR(mode)) str[0]='d';
  if (S_ISCHR(mode)) str[0]='c';
  if (S_ISBLK(mode)) str[0]='b';
  if (mode & S_IRUSR) str[1] = 'r';
  if (mode & S_IWUSR) str[2] = 'w';
  if (mode & S_IXUSR) str[3] = 'x';
  if (mode & S_IRGRP) str[4] = 'r';
  if (mode & S_IWGRP) str[5] = 'w';
  if (mode & S_IXGRP) str[6] = 'x';
  if (mode & S_IROTH) str[7] = 'r';
  if (mode & S_IWOTH) str[8] = 'w';
  if (mode & S_IXOTH) str[9] = 'x';
}
