/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** my_tablen.c
*/

#include "../includes/my.h"

int my_tablen(char **tab)
{
    int i = 0;

    for (; tab[i]; i++);
    return i;
}
