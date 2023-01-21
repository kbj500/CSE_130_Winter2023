/**** Memory.c program for get and set operations ****
 * *************************************************/

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFS 4098

int main() {

    char command[3] = "";
    // int size = 1;
    int file_read = 0;
    char file_name_holder[BUFFS] = "";
    char file_name[BUFFS] = "";
    // char *file_contents = malloc(sizeof(char) * BUFFS);
    char file_contents[BUFFS] = "";
    // char *char_holder = malloc(sizeof(char));

    int bytes_read = 0;
    int total_bytes_read = 0;

    //unsigned int j;
    //for (j = 0; j < strlen(file_name); j++)
    // printf("\n filename[%d]: %c\n", j, file_name[j]);

    //printf("\nfilename size: %lu\n", strlen(file_name));

    //*c = 'c';
    do {
        bytes_read = read(0, command + bytes_read, 4);
        if (bytes_read < 0) {
            //free(file_contents);
            return 1;
        }

        // printf("\nCommand: %s\n", command);

        // unsigned int i;
        //for (i = 0; i < strlen(command); i++)
        //printf("\n Command[%d]: %c\n", i, command[i]);

        //printf("\nBytes Read: %d\n", bytes_read);

        total_bytes_read += bytes_read;

        if (total_bytes_read == 4)
            break;

    } while (bytes_read > 0);

    //printf("\nCommand: %s\n", command);

    //unsigned int i;
    //for (i = 0; i < strlen(command); i++)
    //  printf("\n Command[%d]: %c\n", i, command[i]);

    //printf("\nstarting command check\n");
    // if command is get
    if (strcmp(command, "get ") == 0) {
        // printf("\nget\n");
        // bytes_read = 0;
        // bytes_written = 0;
        // total_bytes_read = 0;

        // printf("\nBytes: %d\n", total_bytes_read);

        /* do { // read file name looping if read fails
       bytes_read = read(0, file_name + bytes_read, BUFFS);
       if (bytes_read < 0) {
         free(file_contents);
         return 1;
       }

       // printf("\nCommand: %s\n", command);

       // unsigned int i;
       // for (i = 0; i < strlen(file_name); i++)
       printf("\n filename: %s\n", file_name);

       printf("\nBytes Read: %d\n", bytes_read);

       if (file_name[strlen(file_name) - 1] == '\n')
         break;

     } while (bytes_read > 0);

     printf("\n filename: %s\n", file_name);*/

        do { // read file name looping if read fails
            bytes_read = read(0, file_name_holder, 1);
            if (bytes_read < 0) {
                //free(file_contents);
                return 1;
            }

            strncat(file_name, file_name_holder, 1);

            if (file_name[strlen(file_name) - 1] == '\0')
                break;

            //printf("\nfilenameholder: %c\n", file_name_holder[0]);
            //   printf("\nCommand: %s\n", command);

            // file_name_holder[0] = '\0';

            //unsigned int i;
            //for (i = 0; i < strlen(file_name); i++)
            //  printf("\n filename[%d]: %c\n", i, file_name[i]);

            //printf("\nBytes Read: %d\n", bytes_read);

        } while (bytes_read > 0);

        if (file_name[strlen(file_name) - 1] != '\n') { // check if formatting is right

            fprintf(
                stderr, "Invalid Command\n"); //: filename does not have newline char for get\n");
            //free(file_contents);
            return 1;

        } else { // delete empty characters

            // printf("\n1filename: %s\n", file_name);
            file_name[strlen(file_name) - 1] = '\0';
            file_name[strlen(file_name) - 1] = '\0';

            //file_name[strlen(file_name) - 1] = '\0';

            //unsigned int i;
            // printf("\nfilename: %s\n", file_name);
            //for (i = 0; i < strlen(file_name); i++)
            //   printf("\n filename[%d]: %c\n", i, file_name[i]);

            file_read = open(file_name, O_RDONLY);

            if (file_read < 0) {
                fprintf(stderr, "Invalid Command\n"); //: open returned <0 for get\n");
                //free(file_contents);
                return 1;
            }

            bytes_read = 0;
            total_bytes_read = 0;

            do {

                bytes_read = read(file_read, file_contents + bytes_read, BUFFS);

                if (bytes_read < 0) {
                    //free(file_contents);
                    return 1;
                }

                else if (bytes_read > 0) {

                    // printf("\nCommand: %s\n", command);

                    //      printf("\nBytes Read: %d\n", bytes_read);

                    int bytes_written = 0;

                    do {
                        int bytes = write(STDOUT_FILENO, file_contents + bytes_written,
                            bytes_read - bytes_written);

                        //        if (bytes <= 0)
                        //            fprintf(stderr, "Could not write to STDOUT\n");

                        bytes_written += bytes;

                        //                     unsigned int i;
                        //                   for (i = 0; i < strlen(file_contents); i++)
                        //                     printf("\n filecontents[%d]: %c\n", i, file_contents[i]);

                        // printf("\nBytes Read: %d\n", bytes_read);

                        //printf("\nBytes Written: %d\n", bytes_written);

                    } while (bytes_written < bytes_read);
                }

            } while (bytes_read > 0);
        }
        //printf("Hello from foo");
        //free(file_contents);
        return 0;

    }

    // if command is set
    else if (strcmp(command, "set ") == 0) {
        // printf("\nset\n");

        bytes_read = 0;
        //unsigned int i;
        //for (i = 0; i < strlen(file_name); i++)
        //  printf("\n filename[%d]: %c\n", i, file_name[i]);

        do { // read file name looping if read fails
            bytes_read = read(0, file_name_holder, 1);
            if (bytes_read < 0) {
                //free(file_contents);
                return 1;
            }

            strncat(file_name, file_name_holder, 1);

            if (file_name[strlen(file_name) - 1] == '\n')
                break;

            //printf("\nfilenameholder: %c\n", file_name_holder[0]);
            //   printf("\nCommand: %s\n", command);

            // file_name_holder[0] = '\0';

            //unsigned int i;
            //for (i = 0; i < strlen(file_name); i++)
            //  printf("\n filename[%d]: %c\n", i, file_name[i]);

            //printf("\nBytes Read: %d\n", bytes_read);

        } while (bytes_read > 0);

        //for (i = 0; i < strlen(file_name); i++)
        //  printf("\n Final filename[%d]: %c\n", i, file_name[i]);

        if (file_name[strlen(file_name) - 1] != '\n') { // check if formatting is right

            fprintf(
                stderr, "Invalid Command\n"); //: filename does not have newline char for set\n");
            //free(file_contents);
            return 1;

        } else { // delete empty characters
            file_name[strlen(file_name) - 1] = '\0';
            //printf("\nfilename: %s\n", file_name);
            //for (i = 0; i < strlen(file_name); i++)
            //  printf("\n filename[%d]: %c\n", i, file_name[i]);

            file_read = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
            //printf("\nfile_read: %d\n", file_read);

            if (file_read < 0) {
                fprintf(stderr, "Invalid Command\n"); //: open returned < 0 for set\n");
                //free(file_contents);
                return 1;
            }

            bytes_read = 0;

            do {

                bytes_read = read(0, file_contents + bytes_read, BUFFS);
                // printf("\nBytes Read: %d\n", bytes_read);
                if (bytes_read < 0) {
                    printf("bytes read < 0");
                    //free(file_contents);
                    return 1;
                }

                else if (bytes_read > 0) {

                    // printf("\nCommand: %s\n", command);

                    //      printf("\nBytes Read: %d\n", bytes_read);

                    int bytes_written = 0;

                    do {
                        int bytes = write(
                            file_read, file_contents + bytes_written, bytes_read - bytes_written);

                        //      if (bytes <= 0)
                        //        fprintf(stderr, "Could not write to STDOUT\n");
                        // file_contents
                        // = realloc(file_contents, sizeof(file_contents) + BUFFS + bytes_written);

                        bytes_written += bytes;

                        //  unsigned int i;
                        //for (i = 0; i < strlen(file_contents); i++)
                        //  printf("\n filecontents[%d]: %c\n", i, file_contents[i]);

                        // printf("\nBytes Read: %d\n", bytes_read);

                        // printf("\nBytes Written: %d\n", bytes_written);

                    } while (bytes_written < bytes_read);
                }

            } while (bytes_read > 0);
        }

        //free(file_contents);
        fprintf(stdout, "OK\n");
        exit(0);
    }

    // if command is neither
    else {
        fprintf(stderr, "Invalid Command\n"); //: initial command did not go through\n");
        //free(file_contents);
        return 1;
    }

    // printf("\nbuff: %s\n", buff);

    /*if (strcmp(buff, "get ") == 0) { // if command is get
    // write(1, buff, 4);
    //
    while (c[0] != '\n') { // read filename
      *c = '\0';

      printf("\nC: %s", c);
      read(0, c, 1);
      if (c[0] == '\n') // end of file name
        break;
      if (c[0] == '\0') { // ended file anme without \n
        free(buff1);
        free(buff2);
        free(c);
        fprintf(stderr, "Invalid Command\n");
        rstrcmp(buff, "get ") == 0eturn 1;
      }
      printf("\nC: %s", c);
      strncat(buff1, c, 1); // load everything in buffer
      s++;
      buff1 = realloc(buff1, s * sizeof(char)); // change buff size per

      // printf("buff1: %s", buff1);

      // printf("while:  %c", c[0]);
    }
    // printf("buff1: %s", buff1);

    // unsigned int i;
    // for (i = 0; i < strlen(buff1); i++)
    //  printf("\nb:'%c'\n", buff1[i]);

    int o = open(buff1, O_RDONLY);

    // printf("o: %d", o);
    if (o < 0) { // if file does not exist
      free(buff1);
      free(buff2);
      free(c);
      fprintf(stderr, "Invalid Command\n");
      return 1;
    }
    int fr = 0;
    int rd;
    int counter = 0;
    while (fr == 0) { // loop thru file reading char by char
      *c = '\0';
      rd = read(o, c, 1);
      printf("\nrd: %d\n", rd);

      // buff2 = realloc(buff2, counter+1);
      strncat(buff2, c, 1);
      if (rd == 0) { // if nothing is read done with code
        fr = 1;
        break;
      }
      counter++;
      // printf("\nCounter: %d\n", counter);

      // printf("\nBuff2:  %lu\n", strlen(buff2));
      buff2 = realloc(buff2, counter + counter * sizeof(char));
      // printf("\nbuff2: %s\n", buff2);
    }
    fprintf(stdout, "%s", buff2);
    free(buff1);
    free(buff2);
    free(c);
    return 0;
  }  else if (strcmp(buff, "set ") == 0) {
       //write(1, buff, 4);

       while (c[0] != '\n') {
           *c = '\0';

           //printf("\nC: %s", c);
           read(0, c, 1);
           if (c[0] == '\n')
               break;
           if (c[0] == '\0') {
               free(buff1);
               free(buff2);
               free(c);
               fprintf(stderr, "Invalid Command\n");
               return 1;
           }
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

       *c = 'c';
       int counter = 0;

       while (c[0] != '\0') {
           *c = '\0';

           // printf("\nC: %s", c);
           read(0, c, 1);
           if (c[0] == '\0')
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
   }*/
}
