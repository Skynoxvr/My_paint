/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** file.c
*/

#include "../includes/my.h"

char *get_str_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    char *data = malloc(1000);

    for (int i = 0; i < 1000; i++)
        data[i] = '\0';
    if (file == NULL)
        return NULL;
    while (getline(&line, &len, file) != -1) {
        strcat(data, line);
    }
    fclose(file);
    return data;
}

char **get_data_from_file(char *filename)
{
    return my_str_to_word_array(get_str_from_file(filename), "\n\0");
}
