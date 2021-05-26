/*

N.B. this is just an exercise to practice with the c language applied to operating systems. The program is full of bugs and for sure it isn't a well done job.
Use it at your own risk :D !
You can test it, modify it and have fun with it (and of me ;D) 
Written by Salvatore Maria Mobilia

*/

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include<dirent.h>
#include <grp.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "functions.c"
#define _GNU_SOURCE
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"




unsigned char *command_buffer;
char *this_dir;
int main()
{
	this_dir =  getcwd(this_dir,PATH_MAX);
	time_t rawtime;
	struct tm * now;
	time ( &rawtime );
	now = localtime ( &rawtime );
	printf("\033[H\033[J");//clear the screen
	printf(ANSI_COLOR_YELLOW "Sessione iniziata : %s \nDigita un comando e se posso ti aiutero' \n",asctime(now)); //time starting session yellow, cause we like it :)
	int _ls = 0;
	while(1)
	{
		char *delim = ">>";
		char *delim1 = "$ ";
		char *user = getUserName();
		user = cat (ANSI_COLOR_GREEN,user);
		user = cat(user,delim);
		user = cat(user,ANSI_COLOR_RESET);
		char *dir = malloc (PATH_MAX*sizeof(*dir));
		dir = getcwd(dir,PATH_MAX);
		dir = cat(ANSI_COLOR_BLUE,dir);
		user = cat(user,dir);
		user = cat(user,ANSI_COLOR_RESET);
		user = cat(user,delim1);	
 		now = localtime ( &rawtime );
		command_buffer = readline(user);//buffer reading
		size_t length = strlen(command_buffer);
		char newbuf[length+1];
		memset(newbuf, '\0', sizeof newbuf);
		strncpy(newbuf, command_buffer, length);
		using_history();
		HISTORY_STATE *myhist = history_get_history_state ();
		HIST_ENTRY **mylist = history_list ();
		if(strlen(command_buffer) > 0)
		{
			add_history(command_buffer);
		}
		
		char * token = strtok(command_buffer, " ");
		
		
		
		if(!strcmp(token,"cd"))//change dir, cd alone not good, program crashes cause no token after cd avaiable
		{
			if(!strcmp(newbuf,"cd"))
			{
				chdir("/home");
			}
			token = strtok(NULL," ");
			if(!strcmp(token,"mum"))
			{
				chdir("/");
				usleep(1);
				continue;
			}
			else
			{
				char *directory = malloc (PATH_MAX*sizeof(*dir));	
				directory = cat(directory,token);
				chdir(directory);
				usleep(1);
				continue;
			}
		}
   		
   		if(!strcmp(token,"touch"))//create a file
   		{
   			int dd;
   			token = strtok(NULL," ");
   			dd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0660);
   			close(dd);
   			continue;
   		}
   		
   		if(!strcmp(token,"rm"))//remove a file
   		{
   			int dd;
   			token = strtok(NULL," ");
   			if(remove(token)!=0)
   			{
   				printf("error deleting file\n");
   			}
   			continue;
   		}
   		
   		if(!strcmp(token,"mkdir"))
   		{
   			token = strtok(NULL," ");
   			if(mkdir(token,0777) == -1){
   				printf("%s already exists, try a different name\n",token);
   				continue;
   			}
   			continue;
   		}
   		
   		if(!strcmp(token,"rmdir"))
   		{
   			token = strtok(NULL," ");
   			if(rmdir(token) == -1){
   				printf("%s folder not empty, cannot remove it\n",token);
   				continue;
   			}
   			continue;
   		}
   		
   		if(!strcmp(token,"ls"))
   		{
   			if(_ls == 0)
   			{
				this_dir = cat(this_dir,"/ls");
				_ls++;
			}
			system(this_dir);
			continue;
   			
   		}
   		
   		if(!strcmp(token,"echo"))//print buffer to file or to console. If ">" is passed  the file will be overwritten, if ">>" is passed buffer will be appended to the file 
   		{	
   			char *nt = strtok(newbuf, " ");
   			char **tokens = malloc(sizeof(newbuf)*numero(newbuf));
   			int i = 0;
   			int dd;
   			while(nt != NULL)
   			{
   				tokens[i] = malloc(sizeof(nt)*strlen(nt));
   				tokens[i] = nt;
   				nt = strtok(NULL , " ");
   				i++;
   			}
   			if(!strcmp(tokens[i-2],">>"))
   			{
   				dd = open(tokens[i-1], O_RDWR | O_CREAT | O_APPEND, 0660);
   				write(dd,"\n",1);
   				for(int j = 1 ; j < i-2; j++)
   				{
   					write(dd,tokens[j],strlen(tokens[j]));
   					write(dd," ",1);
   				}
   				close(dd);
   			}
   			
   			if(!strcmp(tokens[i-2],">"))
   			{
   				dd = open(tokens[i-1], O_RDWR | O_CREAT | O_TRUNC, 0660);
   				for(int j = 1 ; j < i-2; j++)
   				{
   					write(dd,tokens[j],strlen(tokens[j]));
   					write(dd," ",1);
   				}
   				close(dd);
   			}
   			
   			else if(strcmp(tokens[i-2],">") || strcmp(tokens[i-2],">>"))
   			{
   				for(int j = 1; j <= i; j++)
   				{
   					printf("%s ", tokens[j]);	
   				}
   			}
   			continue;
   		}
   	
		if(!strcmp(token,"ciao"))//funzione stupida di test :3
		{
			printf("Ciao! digita un comando e se posso ti aiutero' \n");
			continue;
		}
		
		if(!strcmp(token,"exit") || !strcmp(token,"EXIT") || !strcmp(token,"quit") || !strcmp(token,"QUIT") )//quit my_shell
		{
			printf("Grazie per avermi utilizzato a tuo rischio e pericolo ! Arrivederci :) \n");
			printf( ANSI_COLOR_RED "Sessione terminata alle %s" , asctime(now));
			break;
		}
		
		if(!strcmp(token,"orario") || !strcmp(token,"ORARIO") || !strcmp(token,"ore") || !strcmp(token,"che ore sono"))//local time
		{
			printf("%s",asctime(now));
		}
		
		if(!strcmp(token,"clear"))//clear the screen
		{
			printf("\033[H\033[J");
		}
		
		if(!strcmp(token,"history"))//see commands history
		{
			 for (int i = 0; i < myhist->length; i++)
			 { 
        		printf ("%s\n", mylist[i]->line);
       			//free_history_entry (mylist[i]); if you free the memory and try to run history twice, segfault occurs, use it at your own risk->program will crash :)    
    		}
    		continue;
		}
		
		if(!strcmp(token,"man"))//manual pages for every command implemented in the code
		{
			token = strtok(NULL," ");
			if(token == NULL)
			{
				printf("man of what? Try with man [command]\n");
				continue;
			}
			if(!strcmp(token,"ciao"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN "This is the man page to \" ciao \" command:\nusage:\njust a silly test function, if you write down \"ciao\" a welcome text will appear on screen\npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"cd"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN "This is the man page to \" cd \" command:\nusage:\ntype cd [relative path] to navigate the filesystem\ntype \" [ cd mum ]\" to go to root directory\n [ cd absolute path ] to go to the desired path\npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"history"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" history \" command:\nusage:\ntype history to see all the commands used in the session until that moment\npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"echo"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" echo \" command:\nusage:\ntype echo [string] to print out [string] to console\n type echo [string] >> [filename] to write [string] to [filename] in appending mode\ntype echo [string] > [filename] to write [string] to [filename] in trunc mode\nN.B. [ filename ] can be included in a relative path or you can type the absolute path in which you desire to create the file \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"exit"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" exit \" command:\nusage:\ntype exit to close my_shell \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"touch"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" touch \" command:\nusage:\ntype echo [ filename ] to create [ filename ] in the current directory \n N.B. [ filename ] can be included in a relative path or you can type the absolute path in which you desire to create the file \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"rm"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" rm \" command:\nusage:\ntype rm [ filename ] to remove [ filename ] in the current directory\n N.B. [ filename ] can be included in a relative path or you can type the absolute path in which you desire to create the file \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"orario"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" orario \" command:\nusage:\ntype orario to get the current date and time \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"mkdir"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" mkdir \" command:\nusage:\ntype 'mkdir dir' to create a subfolder in the current directory\n type 'mkdir /path/dir' to create a subfolder in the path specified \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
			
			if(!strcmp(token,"rmdir"))
			{
				printf("\033[H\033[J");
				printf(ANSI_COLOR_CYAN"This is the man page to \" rmdir \" command:\nusage:\ntype 'rmdir dir' to delete a subfolder in the current directory\n type 'rmdir /path/dir' to delete a subfolder in the path specified \npress down 'q' and 'enter' to quit this page\n" ANSI_COLOR_RESET);
				char c[16];
				scanf("%s",c);
				if(c=="q" || c == "quit") continue;
			}
		}
	} 
	
	free(command_buffer);
    exit(0);
    
}
