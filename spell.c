#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]) {
    int n = 0;
    char line[LENGTH + 1];
    char * word = NULL;
    
    if (fp == NULL) {
        return -1;
    } else {
        while (fgets(line, LENGTH, fp) != NULL) {
            word = strtok(line, " ");
            while (word != NULL) {
                char * copy = malloc(sizeof(word));
                strcpy(copy, word);
                copy = removePunctuation(copy);
                if (!check_word(copy, hashtable)) {
                    misspelled[n] = malloc(sizeof(word));
                    strcpy(misspelled[n++], word);
                }
                free(copy);
                copy = NULL;
                word = strtok(NULL, " ");
            }
        }
    }
    free(word);
    word = NULL;
    return n;
}

bool isNumber(const char* word) {
    for (; *word; word++) {
        if (!isdigit(*word)) {
            return false;
        }
    }
    return true;
}

char* removePunctuation(char* word) {
    while (ispunct(*word)) {
        memmove(word, word + 1, strlen(word));
    }
    while (ispunct(word[strlen(word) - 1]) || isspace(word[strlen(word) - 1])) {
        word[strlen(word) - 1] = '\0';
    }
    return word;
}

char* toLowercase(char* word) {
    for (char* t = word; *t; t++) {
        *t = tolower(*t);
    }
    return word;
}

bool findWord(const char* word, hashmap_t hashtable[]) {
    int bucket = hash_function(word);
    struct node* current = hashtable[bucket];
    while (current != NULL) {
        if (strcmp(word, current->word) == 0) {
            return true;
        } else {
            current = current->next;
        }
    }
    free(current);
    current = NULL;
    return false;
}


bool check_word(const char* word, hashmap_t hashtable[]) {
    if (strlen(word) == 0) {
        return false;
    }
    
    if (isNumber(word)) {
        return true;
    }
    
    char * copy = malloc(sizeof(word));
    strcpy(copy, word);
    bool isPresent = findWord(copy, hashtable);
    
    if (!isPresent) {
        copy = toLowercase(copy);
        isPresent = findWord(copy, hashtable);
    }
    
    free(copy);
    copy = NULL;
    return isPresent;
}

void free_memory(hashmap_t hashtable[], char* misspelled[], int n) {
    int i;
    struct node* current = NULL;
    struct node* next = NULL;
    for (i = 0; i < HASH_SIZE; i++) {
        current = hashtable[i];
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
    }
    current = NULL;
    next = NULL;
    
    for (i = 0; i < n; i++) {
        free(&*misspelled[i]);
        misspelled[i] = NULL;
    }
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    FILE* fp;
    int index;
    
    if (strlen(dictionary_file) > FILE_LENGTH) {
        printf("%s: dictionary file name too long. Try again with shorter name\n", dictionary_file);
        return false;
    }
    
    if ((fp = fopen(dictionary_file, "r")) == NULL) {
        return false;
    } else {
        char word[LENGTH + 1];
        struct node** bucket;
        while (fscanf(fp, "%s", word) == 1) {
            index = hash_function(word);
            bucket = &hashtable[index];
            while (*bucket != NULL) {
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
