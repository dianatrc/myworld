/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/my_world.h"

void raise(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] += ALTITUDE_CHANGE;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
}

void lower(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->map_width)
        return;
    if (y < 0 || y >= map->map_height)
        return;
    map->map_3d[y][x] -= ALTITUDE_CHANGE;
    map->map_2d[y][x] = project_iso_point(x * FACTOR,
        y * FACTOR, map->map_3d[y][x]);
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

static void update_point(map_t *map, int x, int y)
{
    map->map_2d[y][x] = project_iso_point(x * FACTOR, y * FACTOR,
        map->map_3d[y][x]);
}

void modify_point(map_t *map, int x, int y)
{
    if (x < 0 || x >= MAP_X || y < 0 || y > MAP_Y)
        return;
    if (map->tool == RAISE)
        map->map_3d[y][x] += 10;
    if (map->tool == LOWER)
        map->map_3d[y][x] -= 10;
    if (map->tool == LEVEL)
        map->map_3d[y][x] = 0;
    update_point(map, x, y);
}
