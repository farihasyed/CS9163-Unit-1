#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_wordlist.txt"

START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
}
END_TEST

START_TEST(test_dictionary_edge)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(!load_dictionary("random_file.txt", hashtable));
}
END_TEST

START_TEST(test_find_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "hello";
    const char* incorrect_word = "wordl";
    ck_assert(findWord(correct_word, hashtable));
    ck_assert(!findWord(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_isNumber_normal)
{
    char* test_cases[3];
    test_cases[0] = "1234";
    test_cases[1] = "63284";
    test_cases[2] = "number";
    
    int i;
    for (i = 0; i < 3; i++) {
        if (i < 2) {
            ck_assert(isNumber(test_cases[i]));
        } else {
            ck_assert(!isNumber(test_cases[i]));
        }
    }
}
END_TEST

START_TEST(test_isNumber_edge)
{
    char* test_cases[3];
    test_cases[0] = "73956293856583027456683658305638462";
    test_cases[1] = "14mn074numb3r";
    test_cases[2] = "!@#$123!@#$";
    
    int i;
    for (i = 0; i < 3; i++) {
        if (i < 1) {
            ck_assert(isNumber(test_cases[i]));
        } else {
            ck_assert(!isNumber(test_cases[i]));
        }
    }
}
END_TEST

START_TEST(test_removePunctuation_normal)
{
    char* test_cases[3];
    test_cases[0] = "hello world!";
    test_cases[1] = "\"quotes\"";
    test_cases[2] = "123%";
    
    char* no_punctuation[3];
    no_punctuation[0] = "hello world";
    no_punctuation[1] = "quotes";
    no_punctuation[2] = "123";
    
    int i;
    for (i = 0; i < 3; i++) {
        ck_assert(strcmp(removePunctuation(test_cases[i]), no_punctuation[i]) == 0);
    }
    
}
END_TEST

START_TEST(test_removePunctuation_edge)
{
    char* test_cases[5];
    test_cases[0] = "!@#$hello world!@#$\"";
    test_cases[1] = "@#123";
    test_cases[2] = "abc123";
    test_cases[3] = "123abc";
    test_cases[4] = "#$%^";
    
    char* no_punctuation[5];
    no_punctuation[0] = "hello world";
    no_punctuation[1] = "123";
    no_punctuation[2] = "abc123";
    no_punctuation[3] = "123abc";
    no_punctuation[4] = "";
    
    int i;
    for (i = 0; i < 5; i++) {
        ck_assert(strcmp(removePunctuation(test_cases[i]), no_punctuation[i]) == 0);
    }
}
END_TEST

START_TEST(test_toLowercase_normal)
{
    char* test_cases[2];
    test_cases[0] = "Computer";
    test_cases[1] = "Science";
    
    char* lowercase[2];
    lowercase[0] = "computer";
    lowercase[1] = "science";
    
    int i;
    for (i = 0; i < 2; i++) {
        ck_assert(strcmp(toLowercase(test_cases[i]), lowercase[i]) == 0);
    }
}
END_TEST

START_TEST(test_toLowercase_edge)
{
    char* test_cases[3];
    test_cases[0] = "HeLLo WoRLD";
    test_cases[1] = "SWITCH";
    test_cases[2] = "languagE";
    
    char* lowercase[3];
    lowercase[0] = "hello world";
    lowercase[1] = "switch";
    lowercase[2] = "language";
    
    int i;
    for (i = 0; i < 3; i++) {
        ck_assert(strcmp(toLowercase(test_cases[i]), lowercase[i]) == 0);
    }
}
END_TEST


START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* test_cases[5];
    test_cases[0] = "Justice";
    test_cases[1] = "hello";
    test_cases[2] = "1234";
    test_cases[3] = "\"world";
    test_cases[4] = "pl.ace";
    
    int i;
    for (i = 0; i < 5; i++) {
        if (i < 4) {
            ck_assert(check_word(test_cases[i], hashtable));
        } else {
            ck_assert(!check_word(test_cases[i], hashtable));
        }
    }
}
END_TEST

START_TEST(test_check_word_edge)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* test_cases[5];
    test_cases[0] = "!@#$hello!@#$\"";
    test_cases[1] = "abc123";
    test_cases[2] = "123abc";
    test_cases[3] = "@#123";
    test_cases[4] = "#$%^";
    
    int i;
    for (i = 0; i < 5; i++) {
        if (i < 1) {
            ck_assert(check_word(test_cases[i], hashtable));
        } else {
            ck_assert(!check_word(test_cases[i], hashtable));
        }
    }
}
END_TEST

START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_dictionary_normal);
    tcase_add_test(check_word_case, test_dictionary_edge);
    tcase_add_test(check_word_case, test_find_word_normal);
    tcase_add_test(check_word_case, test_isNumber_normal);
    tcase_add_test(check_word_case, test_isNumber_edge);
    tcase_add_test(check_word_case, test_removePunctuation_normal);
    tcase_add_test(check_word_case, test_removePunctuation_edge);
    tcase_add_test(check_word_case, test_toLowercase_normal);
    tcase_add_test(check_word_case, test_toLowercase_edge);
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_word_edge);
    tcase_add_test(check_word_case, test_check_words_normal);
    suite_add_tcase(suite, check_word_case);
    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
