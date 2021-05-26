#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char *getUserName();//returns the username as an array of characters

char* cat(char *s1,char *s2);//concatenates two arrays of characters (no size needed, calculated with strlen)

void *getCurrentDir(void);//gives the current directory

int numero(char *s);//returns the number of elements in a string delim = " ", if you need to change the delimeter, change it in the function (.c file)

#endif
