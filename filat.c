#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct stat attributes;

int main(int argc, char const *argv[]) {

  if(argc != 2)
  {
    printf("Error: you have to write a file!\n" );
    return 0;
  }

  int fd = lstat(argv[1], &attributes);

  printf("------------------- %s ------------------------\n",argv[1]);

  printf("File type \t\t: ");
  mode_t mode = attributes.st_mode;

  if(S_ISBLK(mode) != 0)
    printf("Block Special File\n");
  else if(S_ISCHR(mode) != 0)
    printf("character special file\n");
  else if(S_ISDIR(mode) != 0)
    printf("directory\n");
  else if(S_ISFIFO(mode) != 0)
    printf("Pipe and FIFO special file\n");
  else if(S_ISLNK(mode) != 0)
    printf("Symbolic link\n");
  else if(S_ISREG(mode) != 0)
    printf("regular file\n" );
  else if(S_ISSOCK(mode) != 0)    //works only if -D_XOPEN_SOURCE=500 is written in the gcc command
    printf("socket\n" );
  else
    printf("external link\n" );

  printf("Access privileges \t: " );
  if (S_ISDIR(attributes.st_mode)) printf("d");
  else printf("-");
  if (attributes.st_mode & S_IRUSR) printf("r");
  else printf("-");
  if (attributes.st_mode & S_IWUSR) printf("w");
  else printf("-");
  if (attributes.st_mode & S_IXUSR) printf("x");
  else printf("-");
  if (attributes.st_mode & S_IRGRP) printf("r");
  else printf("-");
  if (attributes.st_mode & S_IWGRP) printf("w");
  else printf("-");
  if (attributes.st_mode & S_IXGRP) printf("x");
  else printf("-");
  if (attributes.st_mode & S_IROTH) printf("r");
  else printf("-");
  if (attributes.st_mode & S_IWOTH) printf("w");
  else printf("-");
  if (attributes.st_mode & S_IXOTH) printf("x");
  else printf("-");
  printf("\n" );

  printf("inode-Number \t\t: %d\n", attributes.st_ino);
  printf("Device numbers \t\t: dev = %d rdev = %d\n",attributes.st_rdev,attributes.st_dev );
  printf("Links count \t\t: %d\n", attributes.st_nlink);
  printf("UID \t\t\t: %d\n",attributes.st_uid );
  printf("GID \t\t\t: %d\n", attributes.st_gid);
  printf("File size \t\t: %d Bytes\n", attributes.st_size);
  printf("Last access \t\t: %s", asctime(gmtime(&attributes.st_atime)));
  printf("Last modification \t: %s", asctime(gmtime(&attributes.st_mtime)));
  printf("Last inode change \t: %s", asctime(gmtime(&attributes.st_ctime)));

  return 0;
}
