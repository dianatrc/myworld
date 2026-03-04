/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#ifndef ISO_PROJ_H_
    #define ISO_PROJ_H_
    #define FACTOR 64

    #include "my_world.h"

sfVector2f project_iso_point(int x, int y, int z, camera_t *camera);
sfVector2f **create_2d_map(int **map_3d, camera_t *camera);
void update_2d_map_points(map_t *map);
int draw_2d_map(sfRenderWindow *window, map_t *map);

#endif
