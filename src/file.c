/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** Map save and load management
*/

#include "../include/iso_proj.h"

void save_file(map_t *map, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (!file)
        return;
    fprintf(file, "%d %d\n", map->map_width, map->map_height);
    for (int i = 0; i < map->map_height; i++) {
        for (int j = 0; j < map->map_width; j++)
            fprintf(file, "%d ", map->map_3d[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);
}

int load_save(map_t *map, const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
        return -1;
    fscanf(file, "%d %d", &map->map_width, &map->map_height);
    for (int i = 0; i < map->map_height; i++)
        for (int j = 0; j < map->map_width; j++)
            fscanf(file, "%d", &map->map_3d[i][j]);
    fclose(file);
    update_2d_map_points(map);
    return 0;
}
