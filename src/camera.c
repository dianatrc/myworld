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

int handle_camera(sfEvent *event, map_t *map)
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
