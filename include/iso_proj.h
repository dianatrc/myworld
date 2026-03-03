/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#ifndef ISO_PROJ_H_
    #define ISO_PROJ_H_
    #define FACTOR 64
    #define OFFSET_X 750
    #define OFFSET_Y 30

sfVector2f project_iso_point(int x, int y, int z);
sfVector2f **create_2d_map(int **map_3d);

#endif
