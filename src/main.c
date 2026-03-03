/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

void handle_mouse_click(sfRenderWindow *window, map_t *map)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2i tile = get_tile_coordinates(&mouse_pos, map->map_2d);

    if (tile.x != -1 && tile.y != -1) {
    }
}

static void game_loop(sfRenderWindow *window, map_t *map)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed) {
            handle_mouse_click(window, map);
        }
    }
    sfRenderWindow_clear(window, sfBlack);
    draw_2d_map(window, map->map_2d);
    sfRenderWindow_display(window);
}

int main(void)
{
    sfRenderWindow *window = create_my_window(1280, 720);
    map_t *map = create_map_t();

    while (sfRenderWindow_isOpen(window)) {
        game_loop(window, map);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
