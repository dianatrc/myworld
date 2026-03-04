/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/iso_proj.h"

static void handle_rotation(sfEvent *event, map_t *map, int *change_made)
{
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyW) {
            map->camera.angle_y += 0.05f;
            *change_made = 1;
        }
        if (event->key.code == sfKeyS) {
            map->camera.angle_y -= 0.05f;
            *change_made = 1;
        }
        if (event->key.code == sfKeyA) {
            map->camera.angle_x -= 0.05f;
            *change_made = 1;
        }
        if (event->key.code == sfKeyD) {
            map->camera.angle_x += 0.05f;
            *change_made = 1;
        }
    }
}

static void handle_offsets(sfEvent *event, map_t *map, int *change_made)
{
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyUp) {
            map->camera.offset_y -= 10;
            *change_made = 1;
        }
        if (event->key.code == sfKeyDown) {
            map->camera.offset_y += 10;
            *change_made = 1;
        }
        if (event->key.code == sfKeyLeft) {
            map->camera.offset_x -= 10;
            *change_made = 1;
        }
        if (event->key.code == sfKeyRight) {
            map->camera.offset_x += 10;
            *change_made = 1;
        }
    }
}

static int handle_camera(sfEvent *event, map_t *map)
{
    int change_made = 0;

    handle_offsets(event, map, &change_made);
    handle_rotation(event, map, &change_made);
    if (event->type == sfEvtMouseWheelScrolled) {
        if (event->mouseWheelScroll.delta > 0)
            map->camera.zoom *= 1.1f;
        else
            map->camera.zoom /= 1.1f;
        change_made = 1;
    }
    return change_made;
}

void handle_mouse_click(sfRenderWindow *window, map_t *map)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2i tile;

    if (mouse_pos.y < 100 && mouse_pos.x < 380) {
        determine_tool(&mouse_pos, map);
        return;
    }
    tile = get_tile_coordinates(&mouse_pos, map->map_2d);
    if (tile.x != -1 && tile.y != -1) {
        if (map->tool == RAISE)
            raise_tile(map, &tile);
        if (map->tool == LOWER)
            lower_tile(map, &tile);
        if (map->tool == LEVEL)
            level_tile(map, &tile);
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

static void game_loop(sfRenderWindow *window, map_t *map)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            handle_mouse_click(window, map);
        if (handle_camera(&event, map))
            update_2d_map_points(map);
        if (event.type == sfEvtKeyPressed)
            pressed_key(&event, map);
    }
    sfRenderWindow_clear(window, sfBlack);
    draw_2d_map(window, map);
    draw_toolbar(window, map);
    sfRenderWindow_display(window);
}

int main(void)
{
    sfRenderWindow *window = create_my_window(1280, 720);
    map_t *map = create_map_t();

    if (!window || !map)
        return 84;
    while (sfRenderWindow_isOpen(window)) {
        game_loop(window, map);
    }
    free_map_t(map);
    sfRenderWindow_destroy(window);
    return 0;
}
