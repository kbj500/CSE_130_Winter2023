/**** Memory.c program for get and set operations ****
 * *************************************************/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main() {

    char buff[4];
    int s = 1;
    char *buff1 = malloc(sizeof(char) * s);

    char *buff2 = malloc(sizeof(char));
    char *c = malloc(sizeof(char));
    *c = 'c';
    read(0, buff, 4);
    //printf("\nbuff: %s\n", buff);

    if (strcmp(buff, "get ") == 0) {
        //write(1, buff, 4);
        while (c[0] != '\n') {
            *c = '\0';

            //printf("\nC: %s", c);
            read(0, c, 1);
            if (c[0] == '\n')
                break;
            //printf("\nC: %s", c);
            strncat(buff1, c, 1);
            s++;
            buff1 = realloc(buff1, s * sizeof(char));

            //printf("buff1: %s", buff1);

            //printf("while:  %c", c[0]);
        }
        //printf("buff1: %s", buff1);

        //unsigned int i;
        //for (i = 0; i < strlen(buff1); i++)
        // printf("\nb:'%c'\n", buff1[i]);

        int o = open(buff1, O_RDONLY);

        //printf("o: %d", o);
        if (o < 0) {
            free(buff1);
            free(buff2);
            free(c);
            fprintf(stderr, "Invalid Command\n");
            return 1;
        }
        int fr = 0;
        int rd;
        int counter = 0;
        while (fr == 0) {
            *c = '\0';
            rd = read(o, c, 1);
            ////printf("\nC: %s\n", c);

            //buff2 = realloc(buff2, counter+1);
            strncat(buff2, c, 1);
            if (rd == 0) {
                fr = 1;
            }
            counter++;
            //printf("\nCounter: %d\n", counter);

            //printf("\nBuff2:  %lu\n", strlen(buff2));
            buff2 = realloc(buff2, counter + counter * sizeof(char));
            //printf("\nbuff2: %s\n", buff2);
        }
        fprintf(stdout, "%s", buff2);
        free(buff1);
        free(buff2);
        free(c);
        return 0;
    } else if (strcmp(buff, "set ") == 0) {
        //write(1, buff, 4);

        while (c[0] != '\n') {
            *c = '\0';

            //printf("\nC: %s", c);
            read(0, c, 1);
            if (c[0] == '\n')
                break;
            // printf("\nC: %s", c);
            strncat(buff1, c, 1);
            s++;
            buff1 = realloc(buff1, s * sizeof(char));

            //printf("buff1: %s", buff1);

            //printf("while:  %c", c[0]);
        }
        //printf("buff1: %s", buff1);
        int o = open(buff1, O_CREAT | O_WRONLY | O_TRUNC, 0666);

        //printf("o: %d", o);

        *c = '\0';
        int counter = 0;

        while (c[0] != '\n') {
            *c = '\0';

            // printf("\nC: %s", c);
            read(0, c, 1);
            if (c[0] == '\n')
                break;
            //printf("\nC: %s", c);
            strncat(buff2, c, 1);
            counter++;
            buff2 = realloc(buff2, counter + counter * sizeof(char));

            //printf("buff1: %s", buff1);

            //printf("while:  %c", c[0]);
        }

        //printf("buff2: %s", buff2);

        write(o, buff2, strlen(buff2));

        free(buff1);
        free(buff2);
        free(c);

        printf("OK");

        return 0;

    } else {

        free(buff1);
        free(buff2);
        free(c);
        fprintf(stderr, "Invalid Command\n");
        return 1;
    }
}
