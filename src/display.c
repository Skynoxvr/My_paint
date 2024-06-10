/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** display.c
*/

#include "../includes/my.h"

void print_all_buttons(all_t *all)
{
    for (button_t *current = all->buttons; current; current = current->next) {
        printf("Button: %s\n", current->content);
        printf("Position: (%.f, %.f)\n",
            sfRectangleShape_getPosition(current->rect).x,
            sfRectangleShape_getPosition(current->rect).y);
        printf("Size: (%.f, %.f)\n",
            sfRectangleShape_getSize(current->rect).x,
            sfRectangleShape_getSize(current->rect).y);
        printf("Options:\n");
        if (current->options == NULL) {
            printf("  No options\n\n");
            continue;
        }
        for (option_t *opt = current->options; opt; opt = opt->next)
            printf("  %s\n", opt->name);
        printf("\n");
    }
}
