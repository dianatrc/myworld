/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

static void free_map_lines(int **map, int lines)
{
    for (int i = 0; i < lines; i++)
        free(map[i]);
}

int **create_3d_map(void)
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
