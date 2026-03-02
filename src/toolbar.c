/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

static void determine_tool(sfVector2i mouse_pos, map_t *map)
{
    if (mouse_pos.x < 100)
        map->tool = 0;
    else if (mouse_pos.x < 200)
        map->tool = 1;
    else if (mouse_pos.x < 300)
        map->tool = 2;
}

void toolbar_click(sfRenderWindow *window, sfEvent event, map_t *map)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    if (event.type == sfEvtMouseButtonPressed) {
        if (mouse_pos.y < 100)
            determine_tool(mouse_pos, map);
    }
}

void draw_toolbar(sfRenderWindow *window, map_t *map)
{
    sfRectangleShape *sh = sfRectangleShape_create();
    sfVector2f size = {1280, 80};

    sfRectangleShape_setSize(sh, size);
    sfRectangleShape_setFillColor(bg, sfColor_fromRGBA(50, 50, 50, 200));
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
    sfRectangleShape_destroy(sh);
}
