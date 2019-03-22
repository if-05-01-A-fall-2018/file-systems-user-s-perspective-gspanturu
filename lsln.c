#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

void printFileTypeT(mode_t mode);
void printPrivileges();
void print(char* name);

struct stat attributes;

int main(int argc, char const *argv[]) {
	DIR *directory;
	struct dirent *dir;
	directory = opendir(".");
	if (directory) {
		while ((dir = readdir(directory)) != NULL) {
			if(dir->d_name[0] != '.'){
				print(dir->d_name);
			}
		}
	closedir(directory);
	}
	return 0;
}

void printFileType(mode_t mode) {
	if(S_ISBLK(mode) != 0)
		printf("b");
	else if(S_ISCHR(mode) != 0)
		printf("c");
	else if(S_ISDIR(mode) != 0)
		printf("d");
	else if(S_ISFIFO(mode) != 0)
		printf("f");
	else if(S_ISLNK(mode) != 0)
		printf("Symbolic link\n");
	else if(S_ISSOCK(mode) != 0)
		printf("s" );
  else if(S_ISREG(mode) != 0)
  	printf("-" );
}

void printPrivileges() {
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
}

void print(char* name) {
	lstat(name, &attributes);
	printFileType(attributes.st_mode);
	printf("  ");
	printPrivileges();
	printf("%5d%5d %5d",attributes.st_uid ,attributes.st_gid, attributes.st_size);
	struct tm * tmp;
	tmp = gmtime(&attributes.st_atime);
	printf("%2d-%2d-%2d %2d:%2d ", tmp->tm_mon + 1 , tmp->tm_mday, (1900 + tmp->tm_year) ,tmp->tm_hour + 1,tmp->tm_min);
	printf("%s\n", name );
}
