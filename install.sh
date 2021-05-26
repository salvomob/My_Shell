#!/bin/sh

sudo apt install libreadline-dev
gcc ls.c -o ls
gcc main.c -o my_shell -lreadline
exit	
