/**** Memory.c program for get and set operations ****
 * *************************************************/

#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int main(){

	char buff[4];
	int s = 1;
	char *buff1 = malloc(sizeof(char)*s);
	char *c = malloc(sizeof(char));
	*c= 'c';
	read(0,buff,4);
	printf("\nbuff: %s\n",buff);

	if(strcmp(buff,"get ")==0){
		write(1,buff,4);
		while(c[0]!='\n'){
			*c ='\0';

			//printf("\nC: %s", c);
			read(0,c,1);
			//printf("\nC: %s", c);
			strncat(buff1,c,1);
			s++;
			buff1 = realloc(buff1, s);

		//printf("buff1: %s", buff1);

		//printf("while:  %c", c[0]);
		}
		//printf("buff1: %s", buff1);

		buff1

	}
	else if(strcmp(buff, "set")==0){	
		write(1,buff,4);
	}
	else{
		write(1,"Invalid command",sizeof("Invalid command"));
	}

}

