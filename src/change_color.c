/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** change_color.c
*/

#include "../includes/my.h"

sfRectangleShape *create_wheel(char const *texture_path)
{
    const sfImage *image = sfImage_createFromFile(texture_path);
    sfTexture *texture;
    sfRectangleShape *rect;

    if (!image) {
        printf("Failed to load texture from file: %s\n", texture_path);
        exit(84);
    }
    texture = sfTexture_createFromImage(image, NULL);
    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){100, 100});
    sfRectangleShape_setTexture(rect, texture, sfTrue);
    sfRectangleShape_setPosition(rect, (sfVector2f){1800, 10});
    return rect;
}

sfColor get_color(all_t *all)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(all->window);
    sfTexture *texture;
    sfImage *image;
    sfColor color;

    if (mouse.x < 0 || mouse.y < 0 || mouse.x >= (int)all->video_mode.width ||
        mouse.y >= (int)all->video_mode.height)
        return sfColor_fromRGB(0, 0, 0);
    texture = sfTexture_create(all->video_mode.width, all->video_mode.height);
    sfTexture_updateFromRenderWindow(texture, all->window, 0, 0);
    image = sfTexture_copyToImage(texture);
    color = sfImage_getPixel(image, mouse.x, mouse.y);
    sfImage_destroy(image);
    sfTexture_destroy(texture);
    return color;
}
