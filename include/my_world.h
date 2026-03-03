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
    #include <SFML/Window/Mouse.h>
    #include <math.h>
    #include <stdlib.h>
    #include "../include/iso_proj.h"

    #include "iso_proj.h"

    #define MAP_X 10
    #define MAP_Y 10
    #define ALTITUDE_CHANGE 10

typedef enum {
    RAISE,
    LOWER,
    LEVEL,
    NONE
} tool_t;

typedef struct {
    int **map_3d;
    sfVector2f **map_2d;
    int map_width;
    int map_height;
    tool_t tool;
} map_t;

sfRenderWindow *create_my_window(int width, int height);
map_t *create_map_t(void);
void free_map_t(map_t *map);
void raise(map_t *map, int x, int y);
void lower(map_t *map, int x, int y);
void modify_point(map_t *map, int x, int y);
void toolbar_click(sfRenderWindow *window, sfEvent event, map_t *map);
void draw_toolbar(sfRenderWindow *window, map_t *map);

#endif
