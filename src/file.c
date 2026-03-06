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

static void apply_new_sizes(map_t *map, int width, int height)
{
    map->new_width = width;
    map->new_height = height;
    regenerate_map(map);
}

int load_save(map_t *map, const char *filename)
{
    FILE *file = fopen(filename, "r");
    int load_width;
    int load_height;

    if (!file)
        return -1;
    if (fscanf(file, "%d %d", &load_width, &load_height) != 2) {
        fclose(file);
        return -1;
    }
    apply_new_sizes(map, load_width, load_height);
    for (int i = 0; i < map->map_height; i++)
        for (int j = 0; j < map->map_width; j++)
            fscanf(file, "%d", &map->map_3d[i][j]);
    fclose(file);
    update_2d_map_points(map);
    return 0;
}
