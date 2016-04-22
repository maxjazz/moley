/*

ls - show directory content

*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>


void do_ls(char []);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_string(int, char []);

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
        dostat(direntp->d_name);
    }
  closedir(dir_ptr);
}

void dostat(char *filename)
{
    struct stat info;
    if (stat(filename, &info) == -1)
      perror(filename);
    else
      show_file_info(filename, &info);
}

void show_file_info(char *fname, struct stat *info_p)
{
  char modestr[11];
  mode_to_string(info_p->st_mode, modestr);
  printf ("%s ", modestr );
  printf ("links: %d ", info_p->st_nlink);
  printf ("user: %d ", info_p->st_uid);
  printf ("group: %d ", info_p->st_gid);
  printf ("size: %lld ", info_p->st_size);
  printf ("modtime: %ld ", info_p->st_mtime);
  printf ("name: %s\n", fname);
}


void mode_to_string(int mode, char str[])
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
