/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

static void determine_tool(sfVector2i *mouse_pos, map_t *map)
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

void toolbar_click(sfRenderWindow *window, sfEvent event, map_t *map)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    if (event.type == sfEvtMouseButtonPressed && mouse_pos.y < 100) {
        determine_tool(&mouse_pos, map);
    }
}

static void button_text(sfRenderWindow *window, sfVector2f *pos, char *str)
{
    sfFont *font = sfFont_createFromFile("include/arial.ttf");
    sfText *text = sfText_create();
    sfVector2f text_pos;

    if (!font)
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
    sfFont_destroy(font);
}

static void draw_button(sfRenderWindow *window, tool_t tool, map_t *map,
    char *text)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f size = {90, 60};
    sfVector2f pos = {tool * 100 + 5, 10};

    sfRectangleShape_setPosition(rect, pos);
    sfRectangleShape_setSize(rect, size);
    if (map->tool == tool)
        sfRectangleShape_setFillColor(rect,
            sfColor_fromRGBA(100, 100, 250, 255));
    else
        sfRectangleShape_setFillColor(rect,
            sfColor_fromRGBA(80, 80, 80, 255));
    sfRectangleShape_setOutlineThickness(rect, 2);
    sfRectangleShape_setOutlineColor(rect, sfWhite);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    button_text(window, &pos, text);
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
