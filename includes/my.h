/*
** EPITECH PROJECT, 2024
** mypaint
** File description:
** my.h
*/

#pragma once

#include <X11/Xlib.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define ORANGE (sfColor_fromRGB(255, 165, 0))
#define BROWN (sfColor_fromRGB(165, 42, 42))
#define PINK (sfColor_fromRGB(255, 192, 203))
#define PURPLE (sfColor_fromRGB(128, 0, 128))
#define GREY (sfColor_fromRGB(128, 128, 128))
#define BEIGE (sfColor_fromRGB(245, 245, 220))
#define WHITE (sfColor_fromRGB(255, 255, 255))
#define BLACK (sfColor_fromRGB(0, 0, 0))
#define RED (sfColor_fromRGB(255, 0, 0))
#define GREEN (sfColor_fromRGB(0, 255, 0))
#define BLUE (sfColor_fromRGB(0, 0, 255))
#define YELLOW (sfColor_fromRGB(255, 255, 0))
#define MAGENTA (sfColor_fromRGB(255, 0, 255))
#define CYAN (sfColor_fromRGB(0, 255, 255))
#define TRANSPARENT (sfColor_fromRGBA(0, 0, 0, 0))
#define TRANSPARENT_BLACK (sfColor_fromRGBA(0, 0, 0, 100))
#define TRANSPARENT_WHITE (sfColor_fromRGBA(255, 255, 255, 100))

enum gui_state_e {
    NONE = 0,
    PRESSED,
    HOVERED
};
typedef struct option_s {
    char *name;
    sfText *text;
    sfRectangleShape *rect;
    enum gui_state_e state;
    struct option_s *next;
}option_t;

typedef struct button_s {
    char *content;
    sfText *text;
    sfRectangleShape *rect;
    enum gui_state_e state;
    struct button_s *next;
    float char_size;
    option_t *options;
    int left_offset;
    int top_offset;
}button_t;

typedef struct {
    char *title;
    char **data;
    button_t *buttons;
    sfVideoMode video_mode;
    sfRenderWindow *window;
    sfEvent event;
    sfFont *font;
    sfRectangleShape *chroma_wheel;
    sfImage *img;
    sfTexture *img_texture;
    sfRectangleShape *img_rect;
    int file_starting_line_index;
    int running;
    float thickness;
    sfColor draw_color;
    sfColor fill_color;
}all_t;

typedef struct {
    sfRectangleShape *rect;
    sfText *text;
}popup_btn_t;

// MATH
int max(int a, int b);
int min(int a, int b);

// THREADS
void check_draw(all_t *all);
void check_fill(all_t *all);

// LIB
int my_tablen(char **tab);
char **my_str_to_word_array(char *str, char *delim);

// EVENTS
void handle_events(all_t *all, sfThread *popup_save_thread,
    sfThread *popup_load_thread);

// INIT
all_t *process_data(char **tab);

// DISPLAY
void print_all_buttons(all_t *all);

// LINKED LISTS
void add_button(button_t **head, button_t *new_button);
void add_option(option_t **head, option_t *new_opt);

// FILE
char **get_data_from_file(char *filename);

// WINDOW
void refresh_window(all_t *all);

// SAVE
void main_save_popup(all_t *all);
int save(sfThread *save_thread);

// color and pipette
sfColor get_color(all_t *all);
sfRectangleShape *create_wheel(char const *texturePath);

// LOAD
void main_load_popup(all_t *all);
int load(sfThread *load_thread);

// COMMON
bool is_mouse_in_btn(sfRenderWindow *window, popup_btn_t *btn);
void draw_popup_btn(sfRenderWindow *window, popup_btn_t *btn);
void handle_text_entered(all_t *all, sfRenderWindow *popup, char *filename,
    sfText *text);
