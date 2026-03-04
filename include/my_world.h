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

    #define MAP_X 10
    #define MAP_Y 10
    #define ALTITUDE_CHANGE 10

typedef enum {
    RAISE,
    LOWER,
    LEVEL,
    NONE
} tool_t;

typedef enum {
    GAME,
    LOAD,
    MENU
} state_t;

typedef struct {
    float angle_x;
    float angle_y;
    float offset_x;
    float offset_y;
    float zoom;
} camera_t;

typedef struct {
    int **map_3d;
    sfVector2f **map_2d;
    int map_width;
    int map_height;
    tool_t tool;
    state_t state;
    sfTexture *menu_pic;
    sfFont *font;
    camera_t camera;
} map_t;

// window.c
sfRenderWindow *create_my_window(int width, int height);
// map.c
map_t *create_map_t(void);
void free_map_t(map_t *map);
// tool.c
void raise_tile(map_t *map, sfVector2i *tile);
void lower_tile(map_t *map, sfVector2i *tile);
void level_tile(map_t *map, sfVector2i *tile);
sfVector2i get_tile_coordinates(sfVector2i *mouse_pos, sfVector2f **map_2d);
// toolbar.c
void determine_tool(sfVector2i *mouse_pos, map_t *map);
sfColor button_color(sfFloatRect *rect, tool_t tool, map_t *map,
    sfVector2i *mouse);
void button_text(sfRenderWindow *window, sfVector2f *pos, char *str);
void draw_toolbar(sfRenderWindow *window, map_t *map);
// menu.c
void draw_menu(sfRenderWindow *window, map_t *map);
void determine_state(sfRenderWindow *window, sfVector2i *mouse_pos, map_t *map);

#endif
