#include<stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include "functions.c"
#define _GNU_SOURCE
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


 int main(int argc,char **argv) 
{
	struct dirent **namelist;
	int n;
	if(argc < 1) 
	{
		exit(EXIT_FAILURE); 
	}
	else if (argc == 1) 
	{
		n=scandir(".",&namelist,NULL,alphasort); 
	}
	else 
	{
		n = scandir(argv[1], &namelist, NULL, alphasort); 
	}
	if(n < 0) 
	{
		perror("scandir");
		exit(EXIT_FAILURE); 
	}
	else
	{
		while (n--) 
		{ 
				struct stat buf;
       				stat(namelist[n]->d_name, &buf);
       				if(S_ISDIR(buf.st_mode))
       				{
       					printf(ANSI_COLOR_BLUE"%s\n"ANSI_COLOR_RESET,namelist[n]->d_name);
       				}
       				else if(buf.st_mode & S_IXUSR)
       				{
       					printf(ANSI_COLOR_GREEN"%s\n"ANSI_COLOR_RESET,namelist[n]->d_name);
       				}	 
					else
					{
       					printf("%s\n",namelist[n]->d_name);
					}
			 free(namelist[n]); 
		}
		free(namelist);
	}
	 exit(EXIT_SUCCESS);
}

