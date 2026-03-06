/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** Toolbar and user interface
*/

#include "../include/iso_proj.h"

static void draw_help_box(sfRenderWindow *window, char *message, sfFont *font)
{
    sfText *text = sfText_create();
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (!font || !text)
        return;
    sfText_setString(text, message);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 14);
    sfText_setFillColor(text, sfYellow);
    sfText_setPosition(text, (sfVector2f){(float)mouse.x + 15,
            (float)mouse.y + 15});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_destroy(text);
}

void help_message_tools(tool_t tool, sfRenderWindow *window, sfFont *font)
{
    if (tool == RAISE)
        draw_help_box(window, "Click to raise ground", font);
    if (tool == LOWER)
        draw_help_box(window, "Click to lower ground", font);
    if (tool == LEVEL)
        draw_help_box(window, "Click to level ground", font);
    if (tool == NONE)
        draw_help_box(window, "Default", font);
    if (tool == SAVE)
        draw_help_box(window, "Save progress", font);
}

void help_message_sizes(input_t input, sfRenderWindow *window, sfFont *font)
{
    if (input == WIDTH)
        draw_help_box(window, "Choose map width", font);
    if (input == HEIGHT)
        draw_help_box(window, "Choose map height", font);
}

static void setup_box(sfRectangleShape *box, sfVector2f *pos, int active)
{
    sfVector2f size = {60, 60};

    sfRectangleShape_setPosition(box, *pos);
    sfRectangleShape_setSize(box, size);
    sfRectangleShape_setOutlineThickness(box, 2);
    if (active)
        sfRectangleShape_setOutlineColor(box, sfYellow);
    else
        sfRectangleShape_setOutlineColor(box, sfWhite);
    sfRectangleShape_setFillColor(box, sfColor_fromRGBA(30, 30, 30, 255));
}

void draw_textbox(sfRenderWindow *window, map_t *map, sfVector2f *pos,
    int active)
{
    sfRectangleShape *box = sfRectangleShape_create();
    sfFloatRect rect = {pos->x, pos->y, 60, 60};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
    char str[5];

    setup_box(box, pos, (int)map->input == active);
    sfRenderWindow_drawRectangleShape(window, box, NULL);
    if (active == 0)
        snprintf(str, 5, "%d", map->new_width);
    else
        snprintf(str, 5, "%d", map->new_height);
    button_text(window, pos, str, map->font);
    if (sfFloatRect_contains(&rect, (float)mouse.x, (float)mouse.y)) {
        if (active == 0)
            help_message_sizes(WIDTH, window, map->font);
        else
            help_message_sizes(HEIGHT, window, map->font);
    }
    sfRectangleShape_destroy(box);
}
