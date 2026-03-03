/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

const sfColor BROWN = {139, 69, 19, 255};

sfVector2f project_iso_point(int x, int y, int z)
{
    sfVector2f point_2d;
    float angle_x = 45 * (M_PI / 180);
    float angle_y = 35 * (M_PI / 180);

    point_2d.x = cos(angle_x) * x - cos(angle_x) * y + OFFSET_X;
    point_2d.y = sin(angle_y) * y + sin(angle_y) * x - z + OFFSET_Y;
    return point_2d;
}

sfVector2f **create_2d_map(int **map_3d)
{
    sfVector2f **map_2d = malloc(sizeof(sfVector2f *) * MAP_Y);

    for (int i = 0; i < MAP_Y; i++) {
        map_2d[i] = malloc(sizeof(sfVector2f) * MAP_X);
        for (int j = 0; j < MAP_X; j++)
            map_2d[i][j] = project_iso_point(j * FACTOR, i * FACTOR,
                map_3d[i][j]);
    }
    return map_2d;
}

static sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
    return (vertex_array);
}

static void draw_lines(sfRenderWindow *window, sfVector2f **map_2d,
    int x, int y)
{
    sfVertexArray *line;

    if (x + 1 < MAP_X) {
        line = create_line(&map_2d[y][x], &map_2d[y][x + 1]);
        sfRenderWindow_drawVertexArray(window, line, NULL);
        sfVertexArray_destroy(line);
    }
    if (y + 1 < MAP_Y) {
        line = create_line(&map_2d[y][x], &map_2d[y + 1][x]);
        sfRenderWindow_drawVertexArray(window, line, NULL);
        sfVertexArray_destroy(line);
    }
}

static sfColor get_color(float z)
{
    if (z < 0)
        return sfBlue;
    if (z < 20)
        return sfGreen;
    if (z < 50)
        return BROWN;
    return sfWhite;
}

static void fill_tile(sfVertexArray *array, map_t *map,
    sfVector2i *pos, sfColor *color)
{
    sfVertex v;

    v.color = *color;
    v.position = map->map_2d[pos->y][pos->x];
    sfVertexArray_append(array, v);
    v.position = map->map_2d[pos->y][pos->x + 1];
    sfVertexArray_append(array, v);
    v.position = map->map_2d[pos->y + 1][pos->x + 1];
    sfVertexArray_append(array, v);
    v.position = map->map_2d[pos->y + 1][pos->x];
    sfVertexArray_append(array, v);
}

static void draw_tiles(sfRenderWindow *window, map_t *map, int x, int y)
{
    sfVertexArray *array;
    sfVector2i pos = {x, y};
    float z;
    sfColor color;

    if (x + 1 < MAP_X && y + 1 < MAP_Y) {
        z = (map->map_3d[y][x] + map->map_3d[y][x + 1] +
            map->map_3d[y + 1][x] + map->map_3d[y + 1][x + 1]) / 4.00f;
        color = get_color(z);
        array = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(array, sfQuads);
        fill_tile(array, map, &pos, &color);
        sfRenderWindow_drawVertexArray(window, array, NULL);
        sfVertexArray_destroy(array);
    }
}

int draw_2d_map(sfRenderWindow *window, map_t *map)
{
    for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X; x++) {
            draw_tiles(window, map, x, y);
            draw_lines(window, map->map_2d, x, y);
        }
    }
    return 0;
}
