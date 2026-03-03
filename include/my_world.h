/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** Header file for functions and for includes
*/

#ifndef MY_WORLD_H_
    #define MY_WORLD_H_

    #include <SFML/Graphics.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Window/VideoMode.h>
    #include <SFML/Window/Event.h>
    #include <math.h>
    #include <stdlib.h>

    #include "iso_proj.h"

    #define MAP_X 10
    #define MAP_Y 10
    #define ALTITUDE_CHANGE 10

typedef struct {
    int **map_3d;
    sfVector2f **map_2d;
    int map_width;
    int map_height;
} map_t;

sfRenderWindow *create_my_window(int width, int height);
map_t *create_map_t(void);
void raise(map_t *map, int x, int y);
void lower(map_t *map, int x, int y);
sfVector2i get_tile_coordinates(sfVector2i *mouse_pos, sfVector2f **map_2d);

#endif
