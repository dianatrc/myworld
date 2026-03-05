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
            map->camera.angle_y += ROTATION;
            *change_made = 1;
        }
        if (event->key.code == sfKeyS) {
            map->camera.angle_y -= ROTATION;
            *change_made = 1;
        }
        if (event->key.code == sfKeyA) {
            map->camera.angle_x -= ROTATION;
            *change_made = 1;
        }
        if (event->key.code == sfKeyD) {
            map->camera.angle_x += ROTATION;
            *change_made = 1;
        }
    }
}

static void handle_offsets(sfEvent *event, map_t *map, int *change_made)
{
    sfBool ctrl = sfKeyboard_isKeyPressed(sfKeyLControl)
        || sfKeyboard_isKeyPressed(sfKeyRControl);

    if (event->type == sfEvtKeyPressed && ctrl) {
        if (event->key.code == sfKeyUp)
            map->camera.offset_y -= STEP;
        if (event->key.code == sfKeyDown)
            map->camera.offset_y += STEP;
        if (event->key.code == sfKeyLeft)
            map->camera.offset_x -= STEP;
        if (event->key.code == sfKeyRight)
            map->camera.offset_x += STEP;
        *change_made = 1;
    }
}

static void handle_zoom(sfEvent *event, map_t *map, int *change_made)
{
    if (event->type == sfEvtMouseWheelScrolled) {
        if (event->mouseWheelScroll.delta > 0)
            map->camera.zoom *= ZOOM;
        else
            map->camera.zoom /= ZOOM;
        *change_made = 1;
    }
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyAdd || event->key.code == sfKeyEqual) {
            map->camera.zoom *= ZOOM;
            *change_made = 1;
        }
        if (event->key.code == sfKeySubtract
            || event->key.code == sfKeyHyphen) {
            map->camera.zoom /= ZOOM;
            *change_made = 1;
        }
    }
}

void handle_tile_navigation(sfEvent *event, map_t *map)
{
    sfBool ctrl = sfKeyboard_isKeyPressed(sfKeyLControl)
        || sfKeyboard_isKeyPressed(sfKeyRControl);

    if (event->type == sfEvtKeyPressed && !ctrl) {
        if (event->key.code == sfKeyUp && map->current_tile.y > 0)
            map->current_tile.y--;
        if (event->key.code == sfKeyDown && map->current_tile.y < MAP_Y - 2)
            map->current_tile.y++;
        if (event->key.code == sfKeyLeft && map->current_tile.x > 0)
            map->current_tile.x--;
        if (event->key.code == sfKeyRight && map->current_tile.x < MAP_X - 2)
            map->current_tile.x++;
    }
}

int handle_camera(sfEvent *event, map_t *map)
{
    int change_made = 0;

    handle_offsets(event, map, &change_made);
    handle_rotation(event, map, &change_made);
    handle_zoom(event, map, &change_made);
    return change_made;
}
