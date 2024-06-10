/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** linked_list.c
*/

#include "../includes/my.h"

void add_button(button_t **head, button_t *new)
{
    button_t *last = *head;

    new->next = NULL;
    if (*head == NULL) {
        *head = new;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
    return;
}

void add_option(option_t **head, option_t *new)
{
    option_t *current = *head;

    new->next = NULL;
    if (*head == NULL) {
        *head = new;
        return;
    }
    while (current->next)
        current = current->next;
    current->next = new;
    return;
}
