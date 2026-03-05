/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/iso_proj.h"

void handle_mouse_click(sfRenderWindow *window, map_t *map)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    play_sound(map->click_sound);
    if (mouse_pos.y < 100 && mouse_pos.x < 500) {
        determine_tool(&mouse_pos, map);
        return;
    }
    map->current_tile = get_tile_coordinates(&mouse_pos, map->map_2d,
        map->map_height, map->map_width);
    if (map->current_tile.x != -1 && map->current_tile.y != -1) {
        if (map->tool == RAISE)
            raise_tile(map, &map->current_tile);
        if (map->tool == LOWER)
            lower_tile(map, &map->current_tile);
        if (map->tool == LEVEL)
            level_tile(map, &map->current_tile);
    }
}

static void pressed_key(sfEvent *event, map_t *map)
{
    if (event->key.code == sfKeyNum1)
        map->tool = RAISE;
    if (event->key.code == sfKeyNum2)
        map->tool = LOWER;
    if (event->key.code == sfKeyNum3)
        map->tool = LEVEL;
}

static void handle_events(sfRenderWindow *window, map_t *map, sfEvent *event)
{
    sfVector2i mouse_pos;

    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event->type == sfEvtMouseButtonPressed) {
        if (map->state == MENU) {
            mouse_pos = sfMouse_getPositionRenderWindow(window);
            determine_state(window, &mouse_pos, map);
            play_sound(map->click_sound);
        } else {
            handle_mouse_click(window, map);
        }
    }
    if (handle_camera(event, map))
        update_2d_map_points(map);
    if (event->type == sfEvtKeyPressed) {
        handle_tile_navigation(event, map);
        pressed_key(event, map);
    }
}

static void game_loop(sfRenderWindow *window, map_t *map)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event))
        handle_events(window, map, &event);
    sfRenderWindow_clear(window, sfBlack);
    if (map->state == MENU) {
        draw_menu(window, map);
    } else {
        draw_2d_map(window, map);
        draw_toolbar(window, map);
    }
    sfRenderWindow_display(window);
}

int main(void)
{
    sfRenderWindow *window = create_my_window(1280, 720);
    map_t *map = create_map_t();

    if (!window || !map)
        return 84;
    while (sfRenderWindow_isOpen(window))
        game_loop(window, map);
    free_map_t(map);
    sfRenderWindow_destroy(window);
    return 0;
}
