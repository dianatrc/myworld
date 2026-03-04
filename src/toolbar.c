/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
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

static void help_message(tool_t tool, sfRenderWindow *window, sfFont *font)
{
    if (tool == RAISE)
        draw_help_box(window, "Click to raise ground", font);
    if (tool == LOWER)
        draw_help_box(window, "Click to lower ground", font);
    if (tool == LEVEL)
        draw_help_box(window, "Click to level ground", font);
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
    if (sfFloatRect_contains(&box, (float)mouse.x, (float)mouse.y)) {
        help_message(tool, window, map->font);
    }
    sfRectangleShape_destroy(rect);
}

void draw_toolbar(sfRenderWindow *window, map_t *map)
{
    sfRectangleShape *sh = sfRectangleShape_create();
    sfVector2f size = {300, 80};

    sfRectangleShape_setSize(sh, size);
    sfRectangleShape_setFillColor(sh, sfColor_fromRGBA(50, 50, 50, 200));
    sfRenderWindow_drawRectangleShape(window, sh, NULL);
    sfRectangleShape_destroy(sh);
    draw_button(window, RAISE, map, "RAISE");
    draw_button(window, LOWER, map, "LOWER");
    draw_button(window, LEVEL, map, "LEVEL");
}
