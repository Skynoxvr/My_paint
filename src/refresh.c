/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** refresh.c
*/

#include "../includes/my.h"

void draw_options(all_t *all, button_t *current)
{
    int j = 0;
    int left_offset = 10;
    sfVector2f temp_pos = {0, 0};
    sfVector2f temp_size = {0, 0};

    for (option_t *opt = current->options; opt; opt = opt->next) {
        temp_size.x = sfRectangleShape_getSize(current->rect).x -
            (left_offset * 2);
        temp_size.y = 50;
        temp_pos.x = sfRectangleShape_getPosition(current->rect).x +
            left_offset;
        temp_pos.y = sfRectangleShape_getPosition(current->rect).y +
            sfRectangleShape_getSize(current->rect).y + (temp_size.y * j);
        sfRectangleShape_setSize(opt->rect, temp_size);
        sfRectangleShape_setPosition(opt->rect, temp_pos);
        sfRenderWindow_drawRectangleShape(all->window,
            opt->rect, NULL);
        sfText_setPosition(opt->text, (sfVector2f){temp_pos.x +
            10, temp_pos.y + 10});
        sfRenderWindow_drawText(all->window, opt->text,
            NULL);
        j++;
    }
}

void draw_buttons(all_t *all)
{
    for (button_t *current = all->buttons; current; current = current->next) {
        sfRenderWindow_drawRectangleShape(all->window,
            current->rect, NULL);
        sfRenderWindow_drawText(all->window, current->text,
            NULL);
        sfRenderWindow_drawRectangleShape(all->window,
            all->chroma_wheel, NULL);
        if (current->state == PRESSED)
            draw_options(all, current);
    }
}

void refresh_window(all_t *all)
{
    sfRenderWindow_clear(all->window,
        sfColor_fromRGB(66, 66, 66));
    sfRectangleShape_setTexture(all->img_rect, all->img_texture,
        sfTrue);
    sfRenderWindow_drawRectangleShape(all->window,
        all->img_rect, NULL);
    draw_buttons(all);
    sfRenderWindow_display(all->window);
}
