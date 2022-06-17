#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dict.h"

void clearBuffer()
{
    while ((getchar()) != '\n');
    return;
}

int main()
{
    Dictionary dict;
    int option, dict_option, result;
    char word[MAX_WORD_SIZE], meaning[MAX_MEANING_SIZE];
    memset(word, '\0', sizeof(word));
    memset(meaning, '\0', sizeof(meaning));
    while (1)
    {
        printf("-------------------------------\n");
        printf("1. Import new dictionary\n");
        printf("2. Open dictionary\n");
        printf("3. Add word\n");
        printf("4. Delete word\n");
        printf("5. Modify meaning\n");
        printf("6. Search word\n");
        printf("7. Print dictionary to a dict.txt file\n");
        printf("8. Quit\n");
        printf("-------------------------------\n");
        printf("Select your option: ");
        scanf("%d", &option);
        printf("-------------------------------\n");
        if (option == 1)
        {
            printf("1. English - Latin by freedict.org\n");
            printf("Select dictionary to import (by its number): ");
            scanf("%d", &dict_option);
            int word_counter;
            if (dict_option == 1)
            {
                dict = createDictionary("eng-lat.bt");
                importEngLat(dict, "eng-lat.dict", &word_counter);
            }
            printf("The number of imported headword: %d\n", word_counter);
        }
        if (option == 2)
        {
            printf("*** The dictionary you want to open must be imported before!\n");
            printf("0. Main menu\n");
            printf("1. English - Latin by freedict.org\n");
            printf("Select dictionary to import (by its number): ");
            scanf("%d", &dict_option);
            if (dict_option == 0) continue;
            if (dict_option == 1)
                dict = openDictionary("eng-lat.bt");
            if (dict == NULL)
                printf("Can not open!\n");
            else
                printf("Success!\n");
        }
        if (option == 3)
        {
            clearBuffer();
            printf("Headword: ");
            fgets(word, MAX_WORD_SIZE, stdin);
            word[strlen(word) - 1] = '\0';
            printf("Meaning: ");
            fgets(meaning, MAX_MEANING_SIZE, stdin);
            meaning[strlen(meaning) - 1] = '\0';
            result = addWord(dict, word, meaning);
            if (result == 0)
                printf("Success!\n");
            else
                printf("Error occured! Error code: %d\n", result);
        }
        if (option == 4)
        {
            clearBuffer();
            printf("Headword: ");
            fgets(word, MAX_WORD_SIZE, stdin);
            word[strlen(word) - 1] = '\0';
            result = deleteWord(dict, word);
            if (result == 0)
                printf("Success!\n");
            else
                printf("Error occured! Error code: %d\n", result);
        }
        if (option == 5)
        {
            clearBuffer();
            printf("Headword: ");
            fgets(word, MAX_WORD_SIZE, stdin);
            word[strlen(word) - 1] = '\0';
            printf("Meaning: ");
            fgets(meaning, MAX_MEANING_SIZE, stdin);
            meaning[strlen(meaning) - 1] = '\0';
            result = modifyMeaning(dict, word, meaning);
            if (result == 0)
                printf("Success!\n");
            else
                printf("Error occured! Error code: %d\n", result);
        }
        if (option == 6)
        {
            clearBuffer();
            printf("If you want to stop searching, type \"!quit\" (without quote)\n");
            while (1)
            {
                printf("Headword: ");
                fgets(word, MAX_WORD_SIZE, stdin);
                word[strlen(word) - 1] = '\0';
                if (strcmp(word, "!quit") == 0) break;
                result = searchWord(dict, word, meaning);
                if (result == 0)
                    printf("Meaning:\n%s\n", meaning);
                else
                    printf("Error occured! Error code: %d\n", result);
            }
        }
        if (option == 7)
        {
            printDictionary(dict);
            printf("Success!\n");
        }
        if (option == 8)
        {
            closeDictionary(dict);
            printf("Success!\n");
            break;
        }
    }
    return 0;
}