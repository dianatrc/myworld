/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/iso_proj.h"

static void raise(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] += ALTITUDE_CHANGE;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
}

void raise_tile(map_t *map, sfVector2i *tile)
{
    raise(map, tile->x, tile->y);
    raise(map, tile->x + 1, tile->y);
    raise(map, tile->x, tile->y + 1);
    raise(map, tile->x + 1, tile->y + 1);
}

static void lower(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] -= ALTITUDE_CHANGE;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
}

void lower_tile(map_t *map, sfVector2i *tile)
{
    lower(map, tile->x, tile->y);
    lower(map, tile->x + 1, tile->y);
    lower(map, tile->x, tile->y + 1);
    lower(map, tile->x + 1, tile->y + 1);
}

static void level(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] = 0;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
}

void level_tile(map_t *map, sfVector2i *tile)
{
    level(map, tile->x, tile->y);
    level(map, tile->x + 1, tile->y);
    level(map, tile->x, tile->y + 1);
    level(map, tile->x + 1, tile->y + 1);
}

static float get_distance(sfVector2f *p1, sfVector2f *p2)
{
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

static void update_tile(sfVector2i *tile, float dist, float *min_dist,
    sfVector2i *current)
{
    if (dist < *min_dist) {
        *min_dist = dist;
        tile->x = current->x;
        tile->y = current->y;
    }
}

sfVector2i get_tile_coordinates(sfVector2i *mouse_pos, sfVector2f **map_2d)
{
    sfVector2f m_pos = {(float)mouse_pos->x, (float)mouse_pos->y};
    sfVector2i tile = {-1, -1};
    sfVector2f center;
    sfVector2i current;
    float min_dist = INFINITY;
    float dist;

    for (int i = 0; i < MAP_Y - 1; i++) {
        for (int j = 0; j < MAP_X - 1; j++) {
            center.x = (map_2d[i][j].x + map_2d[i][j + 1].x +
                map_2d[i + 1][j].x + map_2d[i + 1][j + 1].x) / 4.0f;
            center.y = (map_2d[i][j].y + map_2d[i][j + 1].y +
                map_2d[i + 1][j].y + map_2d[i + 1][j + 1].y) / 4.0f;
            dist = get_distance(&m_pos, &center);
            current.x = j;
            current.y = i;
            update_tile(&tile, dist, &min_dist, &current);
        }
    }
    return tile;
}
