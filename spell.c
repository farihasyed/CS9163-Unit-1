#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]) {
    int n = -1;
    if(fp == NULL) {
        return -1;
    } else {
        char word[LENGTH + 1];
        while(fscanf(fp, "%[a-zA-Z]%*[^a-zA-Z]", word) == 1) {
            if(!check_word(word, hashtable)) {
                word[0] = tolower(word[0]);
                if(!check_word(word, hashtable)) {
                    n++;
                    printf("%s is not spelled correctly\n", word);
                    misspelled[n] = malloc(sizeof(word));
                    strcpy(misspelled[n], word);
                }
                else {
                    printf("%s is spelled correctly\n", word);
                }
            }
            else {
                printf("%s is spelled correctly\n", word);
            }
        }
    }
    int i;
    for (i = 0; i < n + 1; i++) {
        printf("%s\n", misspelled[i]);
    }
    return n + 1;
}

bool check_word(const char* word, hashmap_t hashtable[]) {
    int bucket = hash_function(word);
    struct node* current = hashtable[bucket];
    while(current != NULL) {
        if(strcmp(word, current->word) == 0) {
            return true;
        } else {
            current = current->next;
        }
    }
    free(current);
    current = NULL;
    return false;
}

void free_memory(hashmap_t hashtable[], char* misspelled[], int n) {
    int i;
    int j = 0;
    struct node* current;
    struct node* next;
    for (i = 0; i < HASH_SIZE; i++) {
        current = hashtable[i];
        while(current != NULL) {
            next = current->next;
            free(current);
            current = next;
            j++;
        }
    }
    current = NULL;
    next = NULL;
    
    for (i = 0; i < n; i++) {
        free(misspelled[i]);
        misspelled[i] = NULL;
    }
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    FILE* fp;
    int index;
    if((fp = fopen(dictionary_file, "r")) == NULL) {
        return false;
    } else {
        char word[LENGTH + 1];
        struct node** bucket;
        while(fscanf(fp, "%s", word) == 1) {
            index = hash_function(word);
            bucket = &hashtable[index];
            while(*bucket != NULL) {
                bucket = &(*bucket)->next;
            }
            *bucket = malloc(sizeof(**bucket));
            strcpy((*bucket)->word, word);
            (*bucket)->next = NULL;
        }
        fclose(fp);
    }
    return true;
}

//figure out when/how to free shit
