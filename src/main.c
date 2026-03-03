/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

static void pressed_key(sfEvent *event, map_t *map)
{
    if (event->key.code == sfKeyNum1)
        map->tool = RAISE;
    if (event->key.code == sfKeyNum2)
        map->tool = LOWER;
    if (event->key.code == sfKeyNum3)
        map->tool = LEVEL;
}

static void game_loop(sfRenderWindow *window, map_t *map)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        toolbar_click(window, event, map);
        if (event.type == sfEvtKeyPressed)
            pressed_key(&event, map);
    }
    sfRenderWindow_clear(window, sfBlack);
    draw_2d_map(window, map->map_2d);
    draw_toolbar(window, map);
    sfRenderWindow_display(window);
}

int main(void)
{
    sfRenderWindow *window = create_my_window(1280, 720);
    map_t *map = create_map_t();

    if (!window || !map)
        return 84;
    map->tool = RAISE;
    while (sfRenderWindow_isOpen(window)) {
        game_loop(window, map);
    }
    free_map_t(map);
    sfRenderWindow_destroy(window);
    return 0;
}
