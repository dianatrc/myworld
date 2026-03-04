/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/iso_proj.h"

static void free_map_lines(int **map, int lines)
{
    for (int i = 0; i < lines; i++)
        free(map[i]);
}

static int **create_3d_map(void)
{
    int **map = malloc(sizeof(int *) * MAP_Y);

    if (!map)
        return NULL;
    for (int i = 0; i < MAP_Y; i++) {
        map[i] = malloc(sizeof(int) * MAP_X);
        if (!map[i]) {
            free_map_lines(map, i);
            free(map);
            return NULL;
        }
    }
    for (int i = 0; i < MAP_Y; i++)
        for (int j = 0; j < MAP_X; j++)
            map[i][j] = 0;
    return map;
}

map_t *create_map_t(void)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    map->map_width = MAP_X;
    map->map_height = MAP_Y;
    map->map_3d = create_3d_map();
    if (!map->map_3d) {
        free(map);
        return NULL;
    }
    map->map_2d = create_2d_map(map->map_3d);
    if (!map->map_2d) {
        for (int i = 0; i < map->map_height; i++)
            free(map->map_3d[i]);
        free(map->map_3d);
        free(map);
        return NULL;
    }
    return map;
}

void free_map_t(map_t *map)
{
    int i = 0;

    if (map == NULL)
        return;
    if (map->map_3d) {
        for (i = 0; i < MAP_Y; i++)
            free(map->map_3d[i]);
        free(map->map_3d);
    }
    if (map->map_2d) {
        for (i = 0; i < MAP_Y; i++)
            free(map->map_2d[i]);
        free(map->map_2d);
    }
    free(map);
}
