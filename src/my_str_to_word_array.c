/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-pierre.lamey
** File description:
** my_str_to_word_array.c
*/

#include "../includes/my.h"

int count_words(char *str, char *delim)
{
    char *token;
    int count = 0;

    for (token = strtok(str, delim); token != NULL;) {
        count++;
        token = strtok(NULL, delim);
    }
    return count;
}

char **my_str_to_word_array(char *str, char *delim)
{
    int i = 0;
    char *token;
    char *copy = strdup(str);
    int nb_words = count_words(copy, delim);
    char **tab = malloc(sizeof(char *) * (nb_words + 1));
    char *str_bis = strdup(str);

    free(copy);
    if (tab == NULL)
        return NULL;
    for (token = strtok(str_bis, delim); token != NULL;) {
        tab[i] = token;
        if (tab[i] == NULL)
            return NULL;
        i++;
        token = strtok(NULL, delim);
    }
    tab[i] = NULL;
    return tab;
}
