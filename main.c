#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dictionary.h"

int main(int argc, char** args) {
    char file[LENGTH + 1];
    char dictionary[LENGTH + 1];
    node* hashtable[HASH_SIZE] = {0};
    char* misspelled[MAX_MISSPELLED] = {0};
    int n;
    
    if(argc == 3) {
        strcpy(file, args[1]);
        strcpy(dictionary, args[2]);
        if(load_dictionary(dictionary, hashtable)){
            FILE* fp;
            if((fp = fopen(file, "r")) == NULL) {
                printf("Couldn't open file. Exiting program\n");
                exit(1);
            } else {
                char* misspelled[MAX_MISSPELLED] = {0};
                n = checkwords(fp, hashtable, misspelled);
                printf("%d\n", n);
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
