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

static void save_button_actions(map_t *map)
{
    map->tool = SAVE;
    save_file(map, "map.legend");
    if (map->save_sound)
        sfSound_play(map->save_sound);
}

void determine_tool(sfVector2i *mouse_pos, map_t *map)
{
    if (mouse_pos->x < 100) {
        map->tool = RAISE;
        return;
    }
    if (mouse_pos->x < 200) {
        map->tool = LOWER;
        return;
    }
    if (mouse_pos->x < 300) {
        map->tool = LEVEL;
        return;
    }
    if (mouse_pos->x < 400) {
        map->tool = NONE;
        return;
    }
    if (mouse_pos->x < 500) {
        save_button_actions(map);
        return;
    }
}

sfColor button_color(sfFloatRect *rect, tool_t tool, map_t *map,
    sfVector2i *mouse)
{
    if (sfFloatRect_contains(rect, (float)mouse->x, (float)mouse->y))
        return sfColor_fromRGBA(130, 130, 255, 255);
    if (map->tool == tool)
        return sfColor_fromRGBA(100, 100, 250, 255);
    return sfColor_fromRGBA(80, 80, 80, 255);
}

void button_text(sfRenderWindow *window, sfVector2f *pos, char *str,
    sfFont *font)
{
    sfText *text = sfText_create();
    sfVector2f text_pos;

    if (!font || !text)
        return;
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 15);
    sfText_setFillColor(text, sfWhite);
    text_pos.x = pos->x + 15;
    text_pos.y = pos->y + 20;
    sfText_setPosition(text, text_pos);
    sfRenderWindow_drawText(window, text, NULL);
    sfText_destroy(text);
}

static void help_message(tool_t tool, sfRenderWindow *window, sfFont *font,
    input_t input)
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
    if (input == WIDTH)
        draw_help_box(window, "Choose map width", font);
    if (input == HEIGHT)
        draw_help_box(window, "Choose map height", font);
}

static void draw_button(sfRenderWindow *window, tool_t tool, map_t *map,
    char *text)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f size = {90, 60};
    sfVector2f pos = {(float)(tool * 100 + 5), 10};
    sfFloatRect box = {pos.x, pos.y, size.x, size.y};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    sfRectangleShape_setPosition(rect, pos);
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, button_color(&box, tool, map, &mouse));
    sfRectangleShape_setOutlineThickness(rect, 2);
    sfRectangleShape_setOutlineColor(rect, sfWhite);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    button_text(window, &pos, text, map->font);
    if (sfFloatRect_contains(&box, (float)mouse.x, (float)mouse.y))
        help_message(tool, window, map->font, map->input);
    sfRectangleShape_destroy(rect);
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

static void draw_textbox(sfRenderWindow *window, map_t *map, sfVector2f *pos,
    int active)
{
    sfRectangleShape *box = sfRectangleShape_create();
    sfFloatRect rect = {pos->x, pos->y, 60, 60};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
    char str[5];

    setup_box(box, pos, (int)map->input == active);
    sfRenderWindow_drawRectangleShape(window, box, NULL);
    if (active == 0)
        snprintf(str, 5, "%d", map->map_width);
    else
        snprintf(str, 5, "%d", map->map_height);
    button_text(window, pos, str, map->font);
    if (sfFloatRect_contains(&rect, (float)mouse.x, (float)mouse.y)) {
        if (active == 0)
            help_message(NONE, window, map->font, WIDTH);
        else
            help_message(NONE, window, map->font, HEIGHT);
    }
    sfRectangleShape_destroy(box);
}

void draw_toolbar(sfRenderWindow *window, map_t *map)
{
    sfRectangleShape *sh = sfRectangleShape_create();
    sfVector2f size = {650, 80};
    sfVector2f pos_width = {510, 10};
    sfVector2f pos_height = {580, 10};

    sfRectangleShape_setSize(sh, size);
    sfRectangleShape_setFillColor(sh, sfColor_fromRGBA(50, 50, 50, 200));
    sfRenderWindow_drawRectangleShape(window, sh, NULL);
    sfRectangleShape_destroy(sh);
    draw_button(window, RAISE, map, "RAISE");
    draw_button(window, LOWER, map, "LOWER");
    draw_button(window, LEVEL, map, "LEVEL");
    draw_button(window, NONE, map, "NONE");
    draw_button(window, SAVE, map, "SAVE");
    draw_textbox(window, map, &pos_width, 0);
    draw_textbox(window, map, &pos_height, 1);
}
