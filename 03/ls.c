/*

ls - show directory content

*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define PAGEWIDTH 25

struct filebuf
{
  char dir[256];
  char name[256];
  mode_t mode;
  nlink_t nlink;
  uid_t uid;
  gid_t gid;
  struct timespec mtime;
  struct timespec atime;
  struct timespec sctime;
  struct timespec birthtime;
  off_t size;
};


void do_ls(char []);
void simple_ls(char *);
void dostat(char *, char *);

void show_file_info(char *, struct stat *);
void mode_to_string(int, char []);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);
int filenameLen(const char*);


int showFull = 0;
int showHidden = 0;
int showRecursive = 0;

int main (int argc, char *argv[])

{
  char ch;
  int index;
  int opt = 0;

  while ((ch = getopt(argc, argv, "lar"))!=-1)
  {
    switch (ch)
    {
      case 'l': showFull=1; break;
      case 'a': showHidden=1; break;
      case 'r': showRecursive=1; break;
    }
  }

  for (index = optind; index < argc; index++)
  {
    opt = 1;
    printf("%s\n", argv[index] );
    if (showFull == 1)
      do_ls(argv[index]);
    else
      simple_ls(argv[index]);
  }

  if (opt == 0)
  {
    if (showFull == 1)
      do_ls(".");
    else
      simple_ls(".");
  }

}

void simple_ls(char dirname[])
{
  DIR *dir_ptr;
  struct dirent *direntp;
  if ((dir_ptr = opendir (dirname))==NULL)
    fprintf(stderr, "ls: cannot open %s\n", dirname);
  else
    {
      while ((direntp = readdir(dir_ptr))!=NULL)
        printf ("%s \t",direntp->d_name);
    }
      printf("\n");
  closedir(dir_ptr);
}



void do_ls (char *dirname)
{
  DIR *dir_ptr;
  struct dirent *direntp;
  if ((dir_ptr = opendir (dirname))==NULL)
    fprintf(stderr, "ls: cannot open %s\n", dirname);
  else
    {
      while ((direntp = readdir(dir_ptr))!=NULL)
        //printf ("%s\n", dirname);

        dostat(dirname, direntp->d_name);
    }
  closedir(dir_ptr);
}

void dostat(char *directory, char *filename)
{
    struct stat info;
    char fullfile[256];
    //strcat(fullfile, directory);

    strcpy(fullfile,directory);
    strcat(fullfile, "/");
    strcat(fullfile,filename);

    if (stat(fullfile, &info) == -1)
      perror(fullfile);
    else
      show_file_info(fullfile, &info);
}

void show_file_info(char *fname, struct stat *info_p)
{
  char modestr[11];
  mode_to_string(info_p->st_mode, modestr);
  printf ("%s ", modestr );
  printf ("%4d ", (int)info_p->st_nlink);
  printf ("%-8s ", uid_to_name(info_p->st_uid));
  printf ("%-8s ", gid_to_name(info_p->st_gid));
  printf ("%8ld ", (long)info_p->st_size);
  printf ("%.12s ", 4+ctime(&info_p->st_mtime));
  printf ("%s\n", fname);
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
  if (mode & S_ISUID) str[3] = 's';
  if (mode & S_IRGRP) str[4] = 'r';
  if (mode & S_IWGRP) str[5] = 'w';
  if (mode & S_IXGRP) str[6] = 'x';
  if (mode & S_ISGID) str[6] = 's';
  if (mode & S_IROTH) str[7] = 'r';
  if (mode & S_IWOTH) str[8] = 'w';
  if (mode & S_IXOTH) str[9] = 'x';
  if (mode & S_ISVTX) str[9] = 't';
}

#include <pwd.h>
char *uid_to_name(uid_t uid)
{
  struct passwd *getpwuid();
  struct passwd *pw_ptr;
  static char numstr[10];

  if(( pw_ptr = getpwuid(uid)) == NULL)
  {
    sprintf(numstr, "% d", uid);
    return numstr;
  }
  else
    return pw_ptr->pw_name;
}

#include <grp.h>
char *gid_to_name(uid_t gid)
{
  struct group *getgrgid();
  struct group *grp_ptr;
  static char numstr[10];

  if(( grp_ptr = getgrgid(gid)) == NULL)
  {
    sprintf(numstr, "% d", gid);
    return numstr;
  }
  else
    return grp_ptr->gr_name;
}


int filenameLen(const char* str)
{
    int size = 0;
    while(*str++) ++size;
    return size;
}
