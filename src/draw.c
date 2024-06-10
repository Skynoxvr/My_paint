/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** draw.c
*/

#include "../includes/my.h"

void no_lines_cd_bis(all_t *all, int i, int j, sfVector2u img_size)
{
    if (i >= 0 && (uint)i < img_size.x && j >= 0 && (uint)j < img_size.y) {
        sfImage_setPixel(all->img, i, j, all->draw_color);
    }
}

void no_lines_cd(all_t *all, sfMutex *mutex, sfFloatRect bounds)
{
    sfVector2f img_pos = sfRectangleShape_getPosition(all->img_rect);
    sfVector2u img_size = sfImage_getSize(all->img);
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(all->window);
    int start_x = max(0, mouse_pos.x - img_pos.x - all->thickness);
    int start_y = max(0, mouse_pos.y - img_pos.y - all->thickness);
    int end_x = min(bounds.width - 1, mouse_pos.x - img_pos.x +
        all->thickness);
    int end_y = min(bounds.height - 1, mouse_pos.y - img_pos.y +
        all->thickness);

    sfMutex_lock(mutex);
    for (int i = start_x; i <= end_x; i++) {
        for (int j = start_y; j <= end_y; j++) {
            no_lines_cd_bis(all, i, j, img_size);
        }
    }
}

void check_draw(all_t *all)
{
    static sfMutex* mutex = NULL;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(all->img_rect);
    sfVector2i mouse_pos;

    if (!mutex)
        mutex = sfMutex_create();
    while (all->running) {
        if (!sfRenderWindow_hasFocus(all->window))
            continue;
        mouse_pos = sfMouse_getPositionRenderWindow(all->window);
        while (sfMouse_isButtonPressed(sfMouseLeft) &&
            sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
            no_lines_cd(all, mutex, bounds);
            sfMutex_unlock(mutex);
            sfTexture_updateFromImage(all->img_texture, all->img, 0, 0);
        }
    }
    sfMutex_destroy(mutex);
    mutex = NULL;
}
