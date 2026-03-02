/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

sfVector2f project_iso_point(int x, int y, int z)
{
    sfVector2f point_2d;
    float angle_x = 45 * (M_PI / 180);
    float angle_y = 35 * (M_PI / 180);

    point_2d.x = cos(angle_x) * x - cos(angle_x) * y;
    point_2d.y = sin(angle_y) * y + sin(angle_y) * x - z;
    return point_2d;
}

sfVector2f **create_2d_map(int **map_3d)
{
    sfVector2f **map_2d = malloc(sizeof(sfVector2f *) * MAP_Y);

    for (int i = 0; i < MAP_Y; i++) {
        map_2d[i] = malloc(sizeof(sfVector2f) * MAP_X);

        for (int j = 0; j < MAP_X; j++)
            map_2d[i][j] = project_iso_point(j * FACTOR, i * FACTOR, map_3d[i][j]);
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

int draw_2d_map(sfRenderWindow *window, sfVector2f **map_2d)
{
    for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X; x++) {
            if (x + 1 < MAP_X) {
                sfVertexArray *line = create_line(&map_2d[y][x], &map_2d[y][x + 1]);
                sfRenderWindow_drawVertexArray(window, line, NULL);
                sfVertexArray_destroy(line);
            }
            if (y + 1 < MAP_Y) {
                sfVertexArray *line = create_line(&map_2d[y][x], &map_2d[y + 1][x]);
                sfRenderWindow_drawVertexArray(window, line, NULL);
                sfVertexArray_destroy(line);
            }
        }
    }
    return 0;
}
