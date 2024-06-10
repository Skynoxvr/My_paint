/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** events.c
*/

#include "../includes/my.h"

int is_button_clicked(button_t *button, int x, int y)
{
    sfVector2f pos = sfRectangleShape_getPosition(button->rect);
    sfVector2f size = sfRectangleShape_getSize(button->rect);

    if (x >= pos.x && x <= pos.x + size.x && y >= pos.y && y <= pos.y + size.y)
        return 1;
    return 0;
}

void handle_evt_key_pressed(all_t *all, sfThread *popup_save_thread,
    sfThread *popup_load_thread)
{
    if (all->event.key.code == sfKeyS &&
        sfKeyboard_isKeyPressed(sfKeyLControl)) {
        save(popup_save_thread);
        return;
    }
    if (all->event.key.code == sfKeyO &&
        sfKeyboard_isKeyPressed(sfKeyLControl)) {
        load(popup_load_thread);
        return;
    }
    if (all->event.key.code == sfKeyP) {
        all->draw_color = get_color(all);
        all->fill_color = get_color(all);
    }
    if (all->event.key.code == sfKeyUp)
        all->thickness += 1;
    if (all->event.key.code == sfKeyDown) {
        if (all->thickness > 1)
            all->thickness -= 1;
    }
}

void handle_evt_mouse_click(all_t *all)
{
    for (button_t *current = all->buttons; current; current = current->next) {
        if (is_button_clicked(current, all->event.mouseButton.x,
            all->event.mouseButton.y)) {
            current->state = PRESSED;
            printf("Button %s pressed\n", current->content);
            current->state = PRESSED;
        } else
            current->state = NONE;
    }
}

void handle_events(all_t *all, sfThread *popup_save_thread,
    sfThread *popup_load_thread)
{
    if (all->event.type == sfEvtClosed ||
        sfKeyboard_isKeyPressed(sfKeyEscape)) {
        all->running = 0;
        sfRenderWindow_close(all->window);
    } else if (all->event.type == sfEvtMouseButtonPressed) {
        handle_evt_mouse_click(all);
    }
    if (all->event.type == sfEvtKeyPressed)
        handle_evt_key_pressed(all, popup_save_thread, popup_load_thread);
}
