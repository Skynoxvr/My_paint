/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** file.c
*/

#include "../includes/my.h"

sfImage *load_image(const char *filepath)
{
    sfImage *image = sfImage_createFromFile(filepath);

    if (!image) {
        printf("Failed to load image from file: '%s'\n", filepath);
        return NULL;
    }
    return image;
}

popup_btn_t *init_load_btn(all_t *all)
{
    popup_btn_t *load_btn = malloc(sizeof(popup_btn_t));

    load_btn->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(load_btn->rect, (sfVector2f){100, 50});
    sfRectangleShape_setFillColor(load_btn->rect, WHITE);
    sfRectangleShape_setOutlineThickness(load_btn->rect, 2);
    sfRectangleShape_setOutlineColor(load_btn->rect, BLACK);
    sfRectangleShape_setPosition(load_btn->rect, (sfVector2f){370, 10});
    load_btn->text = sfText_create();
    sfText_setString(load_btn->text, "Load");
    sfText_setFont(load_btn->text, all->font);
    sfText_setCharacterSize(load_btn->text, 35);
    sfText_setColor(load_btn->text, BLACK);
    sfText_setPosition(load_btn->text, (sfVector2f){375, 15});
    return load_btn;
}

void draw_popup_btn(sfRenderWindow *window, popup_btn_t *btn)
{
    sfRenderWindow_drawRectangleShape(window, btn->rect, NULL);
    sfRenderWindow_drawText(window, btn->text, NULL);
}

bool is_mouse_in_btn(sfRenderWindow *window, popup_btn_t *btn)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f rect_pos = sfRectangleShape_getPosition(btn->rect);
    sfVector2f rect_size = sfRectangleShape_getSize(btn->rect);

    if ((mouse_pos.x >= rect_pos.x && mouse_pos.x <= rect_pos.x + rect_size.x)
        && (mouse_pos.y >= rect_pos.y && mouse_pos.y <= rect_pos.y +
        rect_size.y))
        return true;
    return false;
}

void handle_button_click_load(all_t *all, sfRenderWindow *window,
    char *filename, popup_btn_t *load_btn)
{
    sfImage *temp;

    if (is_mouse_in_btn(window, load_btn)) {
        temp = load_image(filename);
        if (temp != NULL) {
            all->img = temp;
            sfTexture_updateFromImage(all->img_texture, all->img, 0, 0);
            sfRectangleShape_setTexture(all->img_rect,
                all->img_texture, sfFalse);
            sfRenderWindow_close(window);
        }
    }
}

sfRenderWindow *init_load_window(void)
{
    sfVideoMode popup_mode = {480, 70, 32};

    return sfRenderWindow_create(popup_mode, "Load Image",
        sfClose, NULL);
}

void handle_text_entered(all_t *all, sfRenderWindow *popup, char *filename,
    sfText *text)
{
    if (all->event.text.unicode == 27) {
        while (sfKeyboard_isKeyPressed(sfKeyEscape))
            usleep(100000);
        sfRenderWindow_close(popup);
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyBackspace) && strlen(filename) >= 1) {
        filename[strlen(filename) - 1] = 0;
    } else if (all->event.text.unicode < 128 && all->event.text.unicode != 8 &&
        strlen(filename) < 20) {
        strncat(filename, (char *)&all->event.text.unicode, 1);
    }
    sfText_setString(text, filename);
}

void init_load_txt_rect(all_t *all, sfRectangleShape *rect, sfText *text)
{
    sfText_setFont(text, all->font);
    sfText_setCharacterSize(text, 30);
    sfText_setPosition(text, (sfVector2f){10, 10});
    sfText_setColor(text, BLACK);
    sfRectangleShape_setSize(rect, (sfVector2f){350, 50});
    sfRectangleShape_setFillColor(rect, WHITE);
    sfRectangleShape_setOutlineThickness(rect, 2);
    sfRectangleShape_setOutlineColor(rect, BLACK);
    sfRectangleShape_setPosition(rect, (sfVector2f){10, 10});
}

static void no_lines_refresh_load(sfRenderWindow *popup,
    sfRectangleShape *rect, sfText *text, popup_btn_t *load_btn)
{
    sfRenderWindow_clear(popup, BEIGE);
    sfRenderWindow_drawRectangleShape(popup, rect, NULL);
    sfRenderWindow_drawText(popup, text, NULL);
    draw_popup_btn(popup, load_btn);
    sfRenderWindow_display(popup);
}

void main_load_popup(all_t *all)
{
    sfRenderWindow* popup = init_load_window();
    char filename[256] = {0};
    popup_btn_t *load_btn = init_load_btn(all);
    sfRectangleShape *rect = sfRectangleShape_create();
    sfText* text = sfText_create();

    init_load_txt_rect(all, rect, text);
    while (sfRenderWindow_isOpen(popup)) {
        while (sfRenderWindow_pollEvent(popup, &all->event)) {
            if (all->event.type == sfEvtMouseButtonPressed)
                handle_button_click_load(all, popup, filename, load_btn);
            if (all->event.type == sfEvtTextEntered)
                handle_text_entered(all, popup, filename, text);
            if (all->event.type == sfEvtClosed)
                sfRenderWindow_close(popup);
        }
        no_lines_refresh_load(popup, rect, text, load_btn);
    }
    sfText_destroy(text);
}

int load(sfThread *load_thread)
{
    sfThread_launch(load_thread);
    sfThread_wait(load_thread);
    return 0;
}
