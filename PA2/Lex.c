  // Brian Pereira Alegria
// brpereir
// PA2
// Lex.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 1000

int main(int argc, char *argv[]) {

        int numLine;
        int n, m, k;
        FILE *in, *out;
        char line[MAX_LEN];
        // check that number of command line argument is at least 3
        if (argc != 3) {
                printf("Usage: %s <input file> <output file>\n", argv[0]);
                exit(1);
        }
  
  // open files
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if (in == NULL) {
                printf("Unable to open file %s for reading\n", argv[1]);
                exit(1);
        }
        if (out == NULL) {
                printf("Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }
        numLine = 0;

        // read lines from in
        while (fgets(line, MAX_LEN, in) != NULL) {
                numLine++;
        }
        char *arr[numLine];
        n = 0;
        rewind(in); // set the file position to beginning, instead of closing & opening file again.
        while (fgets(line, MAX_LEN, in) != NULL) {
                arr[n] = malloc((strlen(line)) * sizeof(char *));
                strcpy(arr[n], line);// copy string
                n++;
        }

        List L = newList();
        append(L, 0);

        for (m = 1; m < numLine; m++) {
                moveFront(L);

                while (0 <= index(L)) {
                        if (strcmp(arr[m], arr[get(L)]) < 0) {
                                insertBefore(L, m);
                                break;
                        }
                        moveNext(L);
                }
                if (0 > index(L)) {
                        append(L, m);
                }
        }
        moveFront(L);

        while (0 <= index(L)) {
                fprintf(out, "%s", arr[get(L)]);
                moveNext(L);
        }

        k = 0;
        // close files
        fclose(in);
        fclose(out);
        // free memory
        while(k < m){
                free(arr[k]);
                k++;
        }
        freeList(&L);
}
