#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dictionary.h"

int main(int argc, char** args) {
    char file[FILE_LENGTH + 1];
    char dictionary[FILE_LENGTH + 1];
    struct node* hashtable[HASH_SIZE] = {0};
    char* misspelled[MAX_MISSPELLED] = {0};
    int n;
    
    if(argc == 3) {
        if (strlen(args[1]) > FILE_LENGTH) {
            printf("%s: file name too long. Exiting program\n", args[1]);
            exit(1);
        }
        
        if (strlen(args[2]) > FILE_LENGTH) {
            printf("%s: file name too long. Exiting program\n", args[2]);
            exit(1);
        }
        
        strcpy(file, args[1]);
        strcpy(dictionary, args[2]);
        if(load_dictionary(dictionary, hashtable)){
            FILE* fp;
            if((fp = fopen(file, "r")) == NULL) {
                printf("Couldn't open file %s. Exiting program\n", file);
                exit(1);
            } else {
                n = check_words(fp, hashtable, misspelled);
                printf("The following %d words were misspelled:\n", n);
                int i;
                for (i = 0; i < n; i++) {
                    printf("%s\n", misspelled[i]);
                }
                fclose(fp);
            }
        } else {
            printf("Couldn't open dictionary file. Exiting program\n");
            exit(1);
        }
    } else {
        printf("Incorrect number of arguments. Exiting program\n");
        exit(1);
    }
    free_memory(hashtable, misspelled, n);
    return 0;
}
