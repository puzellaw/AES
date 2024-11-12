
PK_AES: 
	gcc -Wall -Werror -O0 -g -o PK_AES main.c utilities.c

test: 
	gcc function_testing.c  ./Unity-master/src/unity.c -o Testing