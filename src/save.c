/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** file.c
*/

#include "../includes/my.h"

popup_btn_t *init_save_btn(all_t *all)
{
    popup_btn_t *save_btn = malloc(sizeof(popup_btn_t));

    save_btn->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(save_btn->rect, (sfVector2f){100, 50});
    sfRectangleShape_setFillColor(save_btn->rect, WHITE);
    sfRectangleShape_setOutlineThickness(save_btn->rect, 2);
    sfRectangleShape_setOutlineColor(save_btn->rect, BLACK);
    sfRectangleShape_setPosition(save_btn->rect, (sfVector2f){370, 10});

    save_btn->text = sfText_create();
    sfText_setString(save_btn->text, "Save");
    sfText_setFont(save_btn->text, all->font);
    sfText_setCharacterSize(save_btn->text, 35);
    sfText_setColor(save_btn->text, BLACK);
    sfText_setPosition(save_btn->text, (sfVector2f){375, 15});
    return save_btn;
}

popup_btn_t *init_png_btn(all_t *all)
{
    popup_btn_t *png_btn = malloc(sizeof(popup_btn_t));

    png_btn->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(png_btn->rect, (sfVector2f){100, 50});
    sfRectangleShape_setFillColor(png_btn->rect, GREY);
    sfRectangleShape_setOutlineThickness(png_btn->rect, 2);
    sfRectangleShape_setOutlineColor(png_btn->rect, BLACK);
    sfRectangleShape_setPosition(png_btn->rect, (sfVector2f){10, 70});

    png_btn->text = sfText_create();
    sfText_setString(png_btn->text, ".png");
    sfText_setFont(png_btn->text, all->font);
    sfText_setCharacterSize(png_btn->text, 35);
    sfText_setColor(png_btn->text, BLACK);
    sfText_setPosition(png_btn->text, (sfVector2f){15, 75});
    return png_btn;
}

popup_btn_t *init_jpg_btn(all_t *all)
{
    popup_btn_t *jpg_btn = malloc(sizeof(popup_btn_t));

    jpg_btn->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(jpg_btn->rect, (sfVector2f){100, 50});
    sfRectangleShape_setFillColor(jpg_btn->rect, WHITE);
    sfRectangleShape_setOutlineThickness(jpg_btn->rect, 2);
    sfRectangleShape_setOutlineColor(jpg_btn->rect, BLACK);
    sfRectangleShape_setPosition(jpg_btn->rect, (sfVector2f){120, 70});

    jpg_btn->text = sfText_create();
    sfText_setString(jpg_btn->text, ".jpg");
    sfText_setFont(jpg_btn->text, all->font);
    sfText_setCharacterSize(jpg_btn->text, 35);
    sfText_setColor(jpg_btn->text, BLACK);
    sfText_setPosition(jpg_btn->text, (sfVector2f){125, 75});
    return jpg_btn;
}

popup_btn_t *init_bmp_btn(all_t *all)
{
    popup_btn_t *bmp_btn = malloc(sizeof(popup_btn_t));

    bmp_btn->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(bmp_btn->rect, (sfVector2f){100, 50});
    sfRectangleShape_setFillColor(bmp_btn->rect, WHITE);
    sfRectangleShape_setOutlineThickness(bmp_btn->rect, 2);
    sfRectangleShape_setOutlineColor(bmp_btn->rect, BLACK);
    sfRectangleShape_setPosition(bmp_btn->rect, (sfVector2f){230, 70});

    bmp_btn->text = sfText_create();
    sfText_setString(bmp_btn->text, ".bmp");
    sfText_setFont(bmp_btn->text, all->font);
    sfText_setCharacterSize(bmp_btn->text, 35);
    sfText_setColor(bmp_btn->text, BLACK);
    sfText_setPosition(bmp_btn->text, (sfVector2f){235, 75});
    return bmp_btn;
}

void draw_popup_btns_list(sfRenderWindow *window, popup_btn_t **btns)
{
    for (int i = 0; i < 4; i++)
        draw_popup_btn(window, btns[i]);
}

int screen_shot(all_t *all, char *filename, char *extension)
{
    char *res = malloc(strlen(filename) + strlen(extension) + 1);

    memset(res, 0, strlen(filename) + strlen(extension) + 1);
    strcat(res, filename);
    strcat(res, extension);
    sfImage_saveToFile(all->img, res);
    return 0;
}

char *handle_button_click_save(all_t *all, sfRenderWindow *window, char *filename, char *extension, popup_btn_t **btns)
{
    if (is_mouse_in_btn(window, btns[0])) {
        screen_shot(all, filename, extension);
        sfRenderWindow_close(window);
        return extension;
    }
    if (is_mouse_in_btn(window, btns[1])) {
        sfRectangleShape_setFillColor(btns[1]->rect, GREY);
        sfRectangleShape_setFillColor(btns[2]->rect, WHITE);
        sfRectangleShape_setFillColor(btns[3]->rect, WHITE);
        return ".png";
    }
    if (is_mouse_in_btn(window, btns[2])) {
        sfRectangleShape_setFillColor(btns[2]->rect, GREY);
        sfRectangleShape_setFillColor(btns[1]->rect, WHITE);
        sfRectangleShape_setFillColor(btns[3]->rect, WHITE);
        return ".jpg";
    }
    if (is_mouse_in_btn(window, btns[3])) {
        sfRectangleShape_setFillColor(btns[3]->rect, GREY);
        sfRectangleShape_setFillColor(btns[1]->rect, WHITE);
        sfRectangleShape_setFillColor(btns[2]->rect, WHITE);
        return ".bmp";
    }
    return extension;
}

sfRenderWindow *init_save_window(void)
{
    sfVideoMode popup_mode = {480, 130, 32};
    return sfRenderWindow_create(popup_mode, "Save Image", sfClose, NULL);
}

sfText *init_save_txt_rect(all_t *all, sfRectangleShape *rect)
{
    sfText* text = sfText_create();

    sfText_setFont(text, all->font);
    sfText_setCharacterSize(text, 30);
    sfText_setPosition(text, (sfVector2f){10, 10});
    sfText_setColor(text, BLACK);
    sfRectangleShape_setSize(rect, (sfVector2f){350, 50});
    sfRectangleShape_setFillColor(rect, WHITE);
    sfRectangleShape_setOutlineThickness(rect, 2);
    sfRectangleShape_setOutlineColor(rect, BLACK);
    sfRectangleShape_setPosition(rect, (sfVector2f){10, 10});
    return text;
}

popup_btn_t **init_save_buttons(all_t *all)
{
    popup_btn_t *save_btn = init_save_btn(all);
    popup_btn_t *png_btn = init_png_btn(all);
    popup_btn_t *jpg_btn = init_jpg_btn(all);
    popup_btn_t *bmp_btn = init_bmp_btn(all);
    popup_btn_t **btns = malloc(sizeof(popup_btn_t *) * 5);
    btns[0] = save_btn;
    btns[1] = png_btn;
    btns[2] = jpg_btn;
    btns[3] = bmp_btn;
    return btns;
}

void no_lines_refresh_save(sfRenderWindow *popup, sfRectangleShape *rect, sfText *text, popup_btn_t **btns)
{
    sfRenderWindow_clear(popup, BEIGE);
    sfRenderWindow_drawRectangleShape(popup, rect, NULL);
    sfRenderWindow_drawText(popup, text, NULL);
    draw_popup_btns_list(popup, btns);
    sfRenderWindow_display(popup);
}

void main_save_popup(all_t *all)
{
    sfRenderWindow* popup = init_save_window();
    sfRectangleShape *rect = sfRectangleShape_create();
    sfText* text = init_save_txt_rect(all, rect);
    char *extension = ".png";
    char filename[256] = {0};
    popup_btn_t **btns = init_save_buttons(all);


    while (sfRenderWindow_isOpen(popup)) {
        while (sfRenderWindow_pollEvent(popup, &all->event)) {
            if (all->event.type == sfEvtMouseButtonPressed)
                extension = handle_button_click_save(all, popup,
                    filename, extension, btns);
            if (all->event.type == sfEvtTextEntered)
                handle_text_entered(all, popup, filename, text);
            if (all->event.type == sfEvtClosed)
                sfRenderWindow_close(popup);
        }
        no_lines_refresh_save(popup, rect, text, btns);
    }
    sfText_destroy(text);
}

int save(sfThread *popup_thread)
{
    sfThread_launch(popup_thread);
    sfThread_wait(popup_thread);
    return 0;
}
