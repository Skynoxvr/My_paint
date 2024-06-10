/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** fill.c
*/

#include "../includes/my.h"

void fill_node(all_t *all, sfVector2f vector, sfColor old_color, sfColor new_color)
{
    sfVector2f rect_pos = sfRectangleShape_getPosition(all->img_rect);
    sfVector2f rect_size = sfRectangleShape_getSize(all->img_rect);
    int queue_size = rect_size.x * rect_size.y;
    sfVector2i* queue = malloc(sizeof(sfVector2i) * queue_size);
    int front = 0;
    int back = 1;
    int x = vector.x;
    int y = vector.y;

    if (x < 0 || x >= rect_size.x || y < 0 || y >= rect_size.y) {
        free(queue);
        return;
    }
    queue[0] = (sfVector2i){x, y};
    while (front != back) {
        sfVector2i pos = queue[front];
        front = (front + 1) % queue_size;
        if (sfColor_toInteger(sfImage_getPixel(all->img, pos.x, pos.y)) == sfColor_toInteger(old_color) &&
            pos.x >= 0 && pos.x < rect_pos.x + rect_size.x - 1 && pos.y >= 0 && pos.y < rect_pos.y + rect_size.y - 1) {
            sfImage_setPixel(all->img, pos.x, pos.y, new_color);
            if (pos.x + 1 < rect_size.x)
                queue[back] = (sfVector2i){pos.x + 1, pos.y}, back = (back + 1) % queue_size;
            if (pos.x - 1 >= 0)
                queue[back] = (sfVector2i){pos.x - 1, pos.y}, back = (back + 1) % queue_size;
            if (pos.y + 1 < rect_size.y)
                queue[back] = (sfVector2i){pos.x, pos.y + 1}, back = (back + 1) % queue_size;
            if (pos.y - 1 >= 0)
                queue[back] = (sfVector2i){pos.x, pos.y - 1}, back = (back + 1) % queue_size;
        }
    }
    free(queue);
}

void check_fill(all_t *all)
{
    sfVector2f img_pos = sfRectangleShape_getPosition(all->img_rect);
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(all->img_rect);
    sfVector2i mouse_pos;
    sfColor current_color;

    while (all->running) {
        mouse_pos = sfMouse_getPositionRenderWindow(all->window);
        if (all->event.type == sfEvtKeyPressed && all->event.key.code == sfKeySpace &&
            sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
            mouse_pos = sfMouse_getPositionRenderWindow(all->window);
            current_color = sfImage_getPixel(all->img, mouse_pos.x -
                img_pos.x, mouse_pos.y - img_pos.y);
            if (sfColor_toInteger(current_color) == sfColor_toInteger(
                all->fill_color))
                continue;
            fill_node(all, (sfVector2f){mouse_pos.x - img_pos.x, mouse_pos.y - img_pos.y},
                      current_color,
                      all->fill_color);
            sfTexture_updateFromImage(all->img_texture, all->img, 0, 0);
        }
    }
}
