/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

void raise(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] += ALTITUDE_CHANGE;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
}

void lower(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] -= ALTITUDE_CHANGE;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
}

static void update_point(map_t *map, int x, int y)
{
    map->map_2d[y][x] = project_iso_point(x * FACTOR, y * FACTOR,
        map->map_3d[y][x]);
}

void modify_point(map_t *map, int x, int y)
{
    if (x < 0 || x >= MAP_X || y < 0 || y > MAP_Y)
        return;
    if (map->tool == RAISE)
        map->map_3d[y][x] += 10;
    if (map->tool == LOWER)
        map->map_3d[y][x] -= 10;
    if (map->tool == LEVEL)
        map->map_3d[y][x] = 0;
    update_point(map, x, y);
}
