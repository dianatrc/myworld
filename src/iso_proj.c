/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/iso_proj.h"

sfVector2f project_iso_point(int x, int y, int z, camera_t *camera)
{
    sfVector2f point_2d;

    point_2d.x = cos(camera->angle_x) * x - cos(camera->angle_x) * y;
    point_2d.y = sin(camera->angle_y) * y + sin(camera->angle_y) * x - z;
    point_2d.x *= camera->zoom;
    point_2d.y *= camera->zoom;
    point_2d.x += camera->offset_x;
    point_2d.y += camera->offset_y;
    return point_2d;
}

sfVector2f **create_2d_map(int **map_3d, camera_t *camera)
{
    sfVector2f **map_2d = malloc(sizeof(sfVector2f *) * MAP_Y);

    for (int i = 0; i < MAP_Y; i++) {
        map_2d[i] = malloc(sizeof(sfVector2f) * MAP_X);
        for (int j = 0; j < MAP_X; j++)
            map_2d[i][j] = project_iso_point(j * FACTOR, i * FACTOR,
                map_3d[i][j], camera);
    }
    return map_2d;
}

void update_2d_map_points(map_t *map)
{
    for (int i = 0; i < MAP_Y; i++)
        for (int j = 0; j < MAP_X; j++) {
            map->map_2d[i][j] = project_iso_point(j * FACTOR, i * FACTOR,
                map->map_3d[i][j], &map->camera);
        }
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

static sfTexture *get_texture(float z, map_t *map)
{
    if (z < 0)
        return map->water_texture;
    if (z < 20)
        return map->grass_texture;
    if (z < 50)
        return map->dirt_texture;
    return map->snow_texture;
}

static void append_vertex(sfVertexArray *array, sfVector2f *pos,
    sfVector2f *tex, sfColor *color)
{
    sfVertex v;

    v.position = *pos;
    v.texCoords = *tex;
    v.color = *color;
    sfVertexArray_append(array, v);
}

static void fill_tile(sfVertexArray *array, map_t *map,
    sfVector2i *pos)
{
    sfVector2f top_left = {0, 0};
    sfVector2f top_right = {32, 0};
    sfVector2f bottom_left = {0, 32};
    sfVector2f bottom_right = {32, 32};
    sfColor color;

    if (pos->x == map->current_tile.x && pos->y == map->current_tile.y)
        color = sfMagenta;
    else
        color = sfWhite;
    append_vertex(array, &map->map_2d[pos->y][pos->x], &top_left, &color);
    append_vertex(array, &map->map_2d[pos->y][pos->x + 1], &top_right, &color);
    append_vertex(array, &map->map_2d[pos->y + 1][pos->x + 1],
        &bottom_right, &color);
    append_vertex(array, &map->map_2d[pos->y + 1][pos->x],
        &bottom_left, &color);
}

static void draw_tiles(sfRenderWindow *window, map_t *map, int x, int y)
{
    sfVertexArray *array;
    sfVector2i pos = {x, y};
    float z;
    sfRenderStates states = {0};

    if (x + 1 < MAP_X && y + 1 < MAP_Y) {
        z = (map->map_3d[y][x] + map->map_3d[y][x + 1] +
            map->map_3d[y + 1][x] + map->map_3d[y + 1][x + 1]) / 4.00f;
        states.blendMode = sfBlendAlpha;
        states.transform = sfTransform_Identity;
        states.texture = get_texture(z, map);
        states.shader = NULL;
        array = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(array, sfQuads);
        fill_tile(array, map, &pos);
        sfRenderWindow_drawVertexArray(window, array, &states);
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
