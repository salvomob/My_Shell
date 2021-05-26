#include"functions.h"

char *getUserName()
{
 	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw)
	{
		return pw->pw_name;
  	}

  	return "";
}


char* cat(char *s1,char *s2)
{
	unsigned int i1 = strlen(s1);
	unsigned int i2 = strlen(s2);
	unsigned int len = i1+i2;
	char* ret = malloc(len*sizeof(*ret));
	for(int i = 0 ; i < len;i++)
	{
		while(i < i1) 
		{
			ret[i] = s1[i];
			i++;
		}
		while(i>=i1 && i-i1 <= i2 )
		{
			ret[i] = s2[i-i1];
			i++;
		}
	}
	return ret;
}



int numero(char *s)
{
	unsigned int num_words = 1;
	char *delim = " ";	
	int len = strlen(s);
	for(int i = 0; i < len ; i++)
	{
		if(s[i] == *delim)
		{
			num_words++;
		}
	}
	return num_words;
	
}

void *getCurrentDir(void){
    char *currWorkDir, *token;
    char buffer[PATH_MAX + 1];
    char *directory;
    size_t length;

    currWorkDir = getcwd(buffer, PATH_MAX + 1 );
    token = strrchr(currWorkDir, '/');

    if( currWorkDir == NULL ){
        printf("Error"); 
        exit(1);
    }

    if (token == NULL) {
        printf("Error"); 
        exit(1);
    }

    length = strlen(token);
    directory = malloc(length);
    memcpy(directory, token+1, length);

    return directory;
}
