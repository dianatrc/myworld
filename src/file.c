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

static void reallocate_map(map_t *map, int old_height)
{
    for (int i = 0; i < old_height; i++) {
        free(map->map_3d[i]);
        free(map->map_2d[i]);
    }
    free(map->map_2d);
    free(map->map_3d);
    map->map_3d = create_3d_map(map->map_height + 1, map->map_width + 1);
    map->map_2d = create_2d_map(map->map_3d, &map->camera,
        map->map_height + 1, map->map_width + 1);
}

int load_save(map_t *map, const char *filename)
{
    FILE *file = fopen(filename, "r");
    int old_height = map->map_height + 1;

    if (!file)
        return -1;
    fscanf(file, "%d %d", &map->map_width, &map->map_height);
    reallocate_map(map, old_height);
    for (int i = 0; i < map->map_height; i++)
        for (int j = 0; j < map->map_width; j++)
            fscanf(file, "%d", &map->map_3d[i][j]);
    fclose(file);
    update_2d_map_points(map);
    return 0;
}
