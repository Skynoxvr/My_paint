/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** main.c
*/

#include "includes/my.h"

int main(void)
{
    XInitThreads();
    char **data = get_data_from_file("data.mpt");
    all_t *all = process_data(data);
    sfThread *popup_save_thread = sfThread_create(
        (void *) main_save_popup, (void *) all);
    sfThread *popup_load_thread = sfThread_create(
        (void *) main_load_popup, (void *) all);
    sfThread *img_draw_th = sfThread_create(
        (void *) check_draw, (void *) all);
    sfThread *img_fill_th = sfThread_create(
        (void *) check_fill, (void *) all);

    if (all == NULL || all->data == NULL) {
        printf("Memory allocation failed\n");
        return 84;
    }
    print_all_buttons(all);
    usleep(0.01 * 100000);
    sfThread_launch(img_draw_th);
    sfThread_launch(img_fill_th);
    while (sfRenderWindow_isOpen(all->window)) {
        while (sfRenderWindow_pollEvent(all->window, &all->event)) {
            handle_events(all, popup_save_thread, popup_load_thread);
        }
        refresh_window(all);
    }
    sfThread_destroy(popup_load_thread);
    sfThread_destroy(popup_save_thread);
    sfThread_destroy(img_draw_th);
    sfThread_destroy(img_fill_th);
    return 0;
}
