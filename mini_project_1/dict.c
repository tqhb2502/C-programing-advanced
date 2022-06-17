#include <stdlib.h>
#include <string.h>
#include "dict.h"

Dictionary createDictionary(char *dict_file_name)
{
    BTA* btfile;
    btinit();
    btfile = btcrt(dict_file_name, 0, 0);
    return btfile;
}

Dictionary openDictionary(char *dict_file_name)
{
    BTA *btfile;
    btinit();
    btfile = btopn(dict_file_name, 0, 0);
    return btfile;
}

int closeDictionary(Dictionary dict)
{
    if (dict == NULL) return 0;
    btcls(dict);
    return 0;
}

int searchWord(Dictionary dict, char *word, char *meaning)
{
    int rsize;
    int exst = btsel(dict, word, meaning, MAX_MEANING_SIZE, &rsize);
    if (exst == 47) return WNEXIST;
    return 0;
}

int addWord(Dictionary dict, char *word, char *meaning)
{
    char tmp_meaning[MAX_MEANING_SIZE];
    int exst = searchWord(dict, word, tmp_meaning);
    if (exst == 0) return WEXIST;
    btins(dict, word, meaning, MAX_MEANING_SIZE);
    return 0;
}

int deleteWord(Dictionary dict, char *word)
{
    char tmp_meaning[MAX_MEANING_SIZE];
    int exst = searchWord(dict, word, tmp_meaning);
    if (exst != 0) return WNEXIST;
    btdel(dict, word);
    return 0;
}

int modifyMeaning(Dictionary dict, char *word, char *new_meaning)
{
    char tmp_meaning[MAX_MEANING_SIZE];
    int exst = searchWord(dict, word, tmp_meaning);
    if (exst != 0) return WNEXIST;
    btupd(dict, word, new_meaning, MAX_MEANING_SIZE);
    return 0;
}

int printDictionary(Dictionary dict)
{
    FILE *fp;
    fp = fopen("dict.txt", "w");
    char word[MAX_WORD_SIZE], meaning[MAX_MEANING_SIZE];
    int rsize;
    btpos(dict, ZSTART);
    while (btseln(dict, word, meaning, MAX_MEANING_SIZE, &rsize) == 0)
    {
        fputs(word, fp);
        fprintf(fp, "\n");
        fputs(meaning, fp);
        fprintf(fp, "\n");
        fprintf(fp, "---------------------------------------\n");
    }
    fclose(fp);
    return 0;
}

int importEngLat(Dictionary dict, char *text_file_name, int *word_counter)
{
    FILE *fp;
    fp = fopen(text_file_name, "r");
    if (fp == NULL) return CNOFILE;
    char tmp[201], word[MAX_WORD_SIZE], meaning[MAX_MEANING_SIZE];
    memset(word, '\0', sizeof(word));
    memset(meaning, '\0', sizeof(meaning));
    (*word_counter) = 0;
    int word_check, cur_len, prv_line_word = 0, start = 0;
    while (!feof(fp))
    {
        fgets(tmp, 200, fp);
        if (strcmp(tmp, "http://freedict.org/\n") == 0)
        {
            start = 1;
            continue;
        }
        word_check = 1;
        if (start == 0) word_check = 0;
        if (prv_line_word == 1) word_check = 0;
        if ('0' <= tmp[0] && tmp[0] <= '9') word_check = 0;
        if (word_check == 1)
        {
            prv_line_word = 1;
            if ((*word_counter) > 0)
            {
                meaning[strlen(meaning) - 1] = '\0';
                addWord(dict, word, meaning);
                memset(word, '\0', sizeof(word));
                memset(meaning, '\0', sizeof(meaning));
            }
            (*word_counter)++;
            cur_len = (int)strlen(tmp);
            for (int i = 0; i < cur_len; i++)
                if (tmp[i] == '/')
                {
                    strncpy(word, tmp, i - 1);
                    strncpy(meaning, tmp + i, cur_len - 1 - i + 1);
                    break;
                }
        }
        else
        {
            prv_line_word = 0;
            if ((*word_counter) > 0)
                strcat(meaning, tmp);
        }
    }
    addWord(dict, word, meaning);
    fclose(fp);
    return 0;
}