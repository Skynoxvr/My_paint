/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** init.c
*/

#include "../includes/my.h"

option_t *init_options(all_t *all, char *line)
{
    option_t *opts = NULL;
    char **tab = my_str_to_word_array(line, ":");
    option_t *temp;

    if (strlen(line) == 0 || tab == NULL || tab[0] == NULL)
        return NULL;
    for (int i = 0; tab[i]; i++) {
        temp = malloc(sizeof(option_t));
        temp->name = strdup(tab[i]);
        temp->state = NONE;
        temp->next = NULL;
        temp->rect = sfRectangleShape_create();
        sfRectangleShape_setSize(temp->rect,
            (sfVector2f){100, 50});
        sfRectangleShape_setFillColor(temp->rect,
            sfColor_fromRGB(118,118,118));
        sfRectangleShape_setOutlineThickness(temp->rect, 2);
        sfRectangleShape_setOutlineColor(temp->rect, sfBlack);
        temp->text = sfText_create();
        sfText_setString(temp->text, temp->name);
        sfText_setFont(temp->text, all->font);
        sfText_setCharacterSize(temp->text, 20);
        sfText_setColor(temp->text, sfWhite);
        sfText_setOutlineThickness(temp->text, 1);
        sfText_setOutlineColor(temp->text, sfBlack);
        add_option(&opts, temp);
    }
    return opts;
}

button_t *init_button_from_line(all_t *all, char *line)
{
    button_t *button = malloc(sizeof(button_t));
    char **tab = my_str_to_word_array(line, "/");
    char **temp;

    if (my_tablen(tab) < 5)
        return NULL;
    button->next = NULL;
    button->content = strdup(tab[0]);
    button->text = sfText_create();
    sfText_setString(button->text, button->content);
    sfText_setFont(button->text, all->font);
    sfText_setCharacterSize(button->text, atoi(tab[3]));
    sfText_setColor(button->text, sfWhite);
    sfText_setOutlineThickness(button->text, 1);
    sfText_setOutlineColor(button->text, sfBlack);
    temp = my_str_to_word_array(tab[4], ":");
    button->left_offset = atoi(temp[0]);
    button->top_offset = atoi(temp[1]);
    temp = my_str_to_word_array(tab[1], ":");
    button->rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(button->rect, (sfVector2f)
        {atoi(temp[0]), atoi(temp[1])});
    sfText_setPosition(button->text, (sfVector2f){
        atoi(temp[0]) + button->left_offset,
        atoi(temp[1]) + button->top_offset});
    temp = my_str_to_word_array(tab[2], ":");
    sfRectangleShape_setSize(button->rect, (sfVector2f){
        atoi(temp[0]), atoi(temp[1])});
    sfRectangleShape_setFillColor(button->rect,
        sfColor_fromRGB(118,118,118));
    sfRectangleShape_setOutlineThickness(button->rect, 2);
    sfRectangleShape_setOutlineColor(button->rect, sfBlack);
    button->state = NONE;
    if (tab[5] == NULL)
        button->options = NULL;
    else
        button->options = init_options(all, tab[5]);
    return button;
}

button_t *init_buttons(all_t *all)
{
    button_t *head = NULL;
    button_t *temp;

    for (int i = all->file_starting_line_index; all->data[i]; i++) {
        temp = init_button_from_line(all, all->data[i]);
        add_button(&head, temp);
    }
    return head;
}

void no_lines_init_all(all_t *all)
{
    all->draw_color = BLACK;
    all->fill_color = BLACK;
    all->title = "MyPaint";
    all->chroma_wheel = create_wheel("assets/color_circle.png");
    all->window = sfRenderWindow_create(all->video_mode, all->title,
        sfDefaultStyle, NULL);
    all->img_texture = sfTexture_createFromImage(all->img, NULL);
    all->img_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(all->img_rect, (sfVector2f){
        all->video_mode.width - 20, all->video_mode.height - 140});
    sfRectangleShape_setPosition(all->img_rect, (sfVector2f)
        {10, 120});
    sfRectangleShape_setTexture(all->img_rect, all->img_texture,
        sfFalse);
    sfRectangleShape_setOutlineThickness(all->img_rect, 2);
    sfRectangleShape_setOutlineColor(all->img_rect, sfBlack);
}

all_t *process_data(char **tab)
{
    all_t *all = malloc(sizeof(all_t));

    all->thickness = 10;
    all->running = 1;
    all->video_mode = (sfVideoMode){1920, 1080, 32};
    all->img = sfImage_createFromColor(all->video_mode.width - 20,
        all->video_mode.height - 140, WHITE);
    all->data = tab;
    all->font = sfFont_createFromFile("assets/pusab.otf");
    if (all->font == NULL)
        exit(84);
    all->file_starting_line_index = 2;
    all->buttons = init_buttons(all);
    no_lines_init_all(all);
    return all;
}
