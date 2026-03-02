/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#ifndef ISO_PROJ_H_
    #define ISO_PROJ_H_

    #include "../include/my_world.h"

sfVector2f project_iso_point(int x, int y, int z);
sfVector2f **create_2d_map(int **map_3d);
int draw_2d_map(sfRenderWindow *window, sfVector2f **map_2d);

#endif