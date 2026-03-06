/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** Map structure management
*/

#include "../include/iso_proj.h"

static void free_map_lines(int **map, int lines)
{
    for (int i = 0; i < lines; i++)
        free(map[i]);
}

int **create_3d_map(int height, int width)
{
    int **map = malloc(sizeof(int *) * height);

    if (!map)
        return NULL;
    for (int i = 0; i < height; i++) {
        map[i] = malloc(sizeof(int) * width);
        if (!map[i]) {
            free_map_lines(map, i);
            free(map);
            return NULL;
        }
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            map[i][j] = 0;
    return map;
}

static void init_sounds(map_t *map)
{
    map->click_buffer = sfSoundBuffer_createFromFile("utils/click_sound.wav");
    map->click_sound = sfSound_create();
    if (map->click_buffer && map->click_sound)
        sfSound_setBuffer(map->click_sound, map->click_buffer);
    map->save_buffer = sfSoundBuffer_createFromFile("utils/save_sound.wav");
    map->save_sound = sfSound_create();
    if (map->save_buffer && map->save_sound)
        sfSound_setBuffer(map->save_sound, map->save_buffer);
}

static void init_map_variables(map_t *map)
{
    map->map_width = MAP_X;
    map->map_height = MAP_Y;
    map->tool = NONE;
    map->state = MENU;
    map->font = sfFont_createFromFile("utils/arial.ttf");
    map->camera.angle_x = ANGLE_X;
    map->camera.angle_y = ANGLE_Y;
    map->camera.offset_x = START_X;
    map->camera.offset_y = START_Y;
    map->camera.zoom = START_ZOOM;
    map->current_tile.x = -1;
    map->current_tile.y = -1;
    map->menu_pic = sfTexture_createFromFile("utils/world.jpg", NULL);
    map->water_texture = sfTexture_createFromFile("utils/water.png", NULL);
    map->grass_texture = sfTexture_createFromFile("utils/grass.png", NULL);
    map->dirt_texture = sfTexture_createFromFile("utils/dirt.png", NULL);
    map->snow_texture = sfTexture_createFromFile("utils/snow.png", NULL);
    init_sounds(map);
}

static void destroy_textures(map_t *map)
{
    if (map->menu_pic)
        sfTexture_destroy(map->menu_pic);
    if (map->water_texture)
        sfTexture_destroy(map->water_texture);
    if (map->grass_texture)
        sfTexture_destroy(map->grass_texture);
    if (map->dirt_texture)
        sfTexture_destroy(map->dirt_texture);
    if (map->snow_texture)
        sfTexture_destroy(map->snow_texture);
}

static void destroy_sounds(map_t *map)
{
    sfSound_destroy(map->click_sound);
    sfSoundBuffer_destroy(map->click_buffer);
    sfSound_destroy(map->save_sound);
    sfSoundBuffer_destroy(map->save_buffer);
}

map_t *create_map_t(void)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    init_map_variables(map);
    map->map_3d = create_3d_map(map->map_height + 1, map->map_width + 1);
    if (!map->map_3d) {
        if (map->font)
            sfFont_destroy(map->font);
        free(map);
        return NULL;
    }
    map->map_2d = create_2d_map(map->map_3d, &map->camera,
        map->map_height + 1, map->map_width + 1);
    if (!map->map_2d) {
        free_map_t(map);
        return NULL;
    }
    return map;
}

void free_map_t(map_t *map)
{
    int i = 0;

    if (map == NULL)
        return;
    if (map->map_3d) {
        free_map_lines(map->map_3d, map->map_height + 1);
        free(map->map_3d);
    }
    if (map->map_2d) {
        for (i = 0; i < map->map_height + 1; i++)
            free(map->map_2d[i]);
        free(map->map_2d);
    }
    if (map->font)
        sfFont_destroy(map->font);
    destroy_textures(map);
    destroy_sounds(map);
    free(map);
}

void play_sound(sfSound *sound)
{
    if (sound)
        sfSound_play(sound);
}

void regenerate_map(map_t *map)
{
    for (int i = 0; i < map->map_height + 1; i++) {
        free(map->map_3d[i]);
        free(map->map_2d[i]);
    }
    free(map->map_3d);
    free(map->map_2d);
    map->map_3d = create_3d_map(map->map_height + 1, map->map_width + 1);
    map->map_2d = create_2d_map(map->map_3d, &map->camera,
        map->map_height + 1, map->map_width + 1);
}
