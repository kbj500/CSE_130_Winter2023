#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "LinkedList.h"
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    //    printf("\nargc %d\n", argc);
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "wrong arguments\n");
        fprintf(stderr, "usage: ./cacher [-N size] <policy>\n");
        return EXIT_FAILURE;
    }

    int c;
    int L_flag = 0;
    int C_flag = 0;
    unsigned int nsize;
    char *cNum = NULL;

    while ((c = getopt(argc, argv, "N:FLC")) != -1) {
        switch (c) {
        case 'N':
            nsize = (unsigned int) strtoul(optarg, &cNum, 10);
            if (cNum && *cNum != '\0') {
                fprintf(stderr, "invalid cache size: %s", optarg);
                return EXIT_FAILURE;
            }
            //printf("\nN flag true, cache size: %d\n", nsize);
            break;
        case 'F': break;
        case 'L': L_flag = 1; break;
        case 'C': C_flag = 1; break;
        case '?':
            if (optopt == 'c')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default: abort();
        }

        //printf("Flags: F:%d L:%d C: %d", F_flag, L_flag, C_flag);
    }

    char b[BUFFER_SIZE];
    int cm = 0;
    int capm = 0;
    ListItem *l;

    if (!C_flag) {

        queue_t *q = NULL;
        q = queue_new(nsize);

        while (fgets(b, BUFFER_SIZE, stdin)) {
            //       printf("\nBUFF: %s\n", b);

            //	queue_push(q,b);
            //	printChar(q);
            //	*char temp[BUFFER_SIZE];

            //	temp = *b;
            //

            //printf("\n cm: %d\n", cm);
            //printf("\n capm: %d\n", capm);

            int fc = charFind(q, b);
            if (fc > -1) {
                // HIT
                //printf("\nHIT at [%d], %s",fc,b);
                // printf("\n cm: %d\n", cm);
                // printf("\n fc: %d\n", fc);
                fprintf(stdout, "HIT\n");
                if (L_flag) {
                    reOrderChar(q, fc);
                }
            } else {
                if (cm == 0) {
                    l = LinkedListNew(b);
                    cm++;
                } else if (isItemInLinkedList(l, b)) {
                    //printf("\n CAPM miss\n");
                    capm++;
                } else {
                    //printf("\n CM miss\n");
                    LinkedListCreateAfter(LinkedListGetLast(l), b);
                    cm++;
                }
                // MISS
                //printf("\nMISS, %s", b);
                fprintf(stdout, "MISS\n");
                //printf("\n cm: %d\n", cm);
                if (qFull(q)) {

                    char **popcon = malloc(sizeof(char **));
                    queue_pop(q, popcon);
                }
                queue_push(q, b);
            }
            //printChar(q);
        }
        fprintf(stdout, "%d %d\n", cm, capm);
    } else {

        ListItem *cache = LinkedListNew(NULL);

        for (unsigned int i = 0; i < nsize - 1; i++) {
            LinkedListCreateAfter(LinkedListGetLast(cache), NULL);
        }

        setClockHead(cache);
        //      LinkedListPrint(cache);

        while (fgets(b, BUFFER_SIZE, stdin)) {
            //check if b is in list
            ListItem *inList = isItemInLinkedList(cache, b);
            //if in list
            if (inList) {

                //	hit
                //
                fprintf(stdout, "HIT\n");

                //	set ref to 1
                changeRef(inList, 1);
            }
            //else not in list
            else {
                if (cm == 0) {
                    l = LinkedListNew(b);
                    cm++;
                } else if (isItemInLinkedList(l, b)) {
                    //printf("\n CAPM miss\n");
                    capm++;
                } else {
                    //printf("\n CM miss\n");
                    LinkedListCreateAfter(LinkedListGetLast(l), b);
                    cm++;
                }

                //	miss
                fprintf(stdout, "MISS\n");
                //	if list is not full
                ListItem *isNotFull = isListFull(cache);

                if (isNotFull) {

                    //		add at nearest null
                    changeData(isNotFull, b);
                }
                //	else list full
                else {
                    clockHandMiss(cache, b);
                }

                //		traverse till 0 ref
                //
                //		reassign value
            }
            //            LinkedListPrint(cache);
        }
        fprintf(stdout, "%d %d\n", cm, capm);
    }
    /*    queue_t *q = NULL;
    q = queue_new(100);

    char Chars[100][30];

    for(int i = 0; i < 100; i++){
	    sprintf(Chars[i],"%d", i);
    bool  t = queue_push(q, Chars[i]);
    if(t) printf("\n elem successfully  added\n" );
    else printf("\n elem add failed\n");
    }

    bool  t = queue_push(q, "101");
    if(t) printf("\n elem successfully  added\n" );
    else printf("\n elem add failed\n");
    printChar(q);
  


   for(int i = 0; i< 101; i++){
        char ** popcon = malloc(sizeof(char**));
        queue_pop(q, popcon);
        printf("\n %s popped\n",*popcon);
    }

   int f = findChar(q, "77");
   if(f > -1){ 
	   printf("\nchar found\n");
	   reOrderChar(q, f);
	   printChar(q);
   }
   else printf("\nchar not found\n");


    int d = findChar(q, "101");
    if(d > -1){
           printf("\nchar found\n");
           reOrderChar(q, d);
           printChar(q);
   }
   else printf("\nchar not found\n");
*/
    return 0;
}
