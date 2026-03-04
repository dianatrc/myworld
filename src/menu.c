/*
** EPITECH PROJECT, 2026
** MY_WORLD
** File description:
** MY_WORLD project
*/

#include "../include/iso_proj.h"

static void draw_title(sfRenderWindow *window, sfVector2f *pos, sfFont *font)
{
    const char *title = "My world";
    sfText *text = sfText_create();

    if (!text)
        return;
    sfText_setString(text, title);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 80);
    sfText_setFillColor(text, sfWhite);
    sfText_setPosition(text, *pos);
    sfRenderWindow_drawText(window, text, NULL);
    sfText_destroy(text);
}

static void draw_menu_button(sfRenderWindow *window, map_t *map,
    sfVector2f *pos, const char *title)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f size = {90, 60};
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfFloatRect box = {pos->x, pos->y, size.x, size.y};
    sfColor color;

    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setPosition(rect, *pos);
    sfRectangleShape_setOutlineThickness(rect, 2);
    sfRectangleShape_setOutlineColor(rect, sfWhite);
    color = button_color(&box, NONE, map, &mouse_pos);
    sfRectangleShape_setFillColor(rect, color);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    button_text(window, pos, (char *)title, map->font);
    sfRectangleShape_destroy(rect);
}

void draw_menu(sfRenderWindow *window, map_t *map)
{
    sfVector2f title_pos = {50, 300};
    sfVector2f start_pos = {20, 20};
    sfVector2f load_pos = {120, 20};
    sfVector2f exit_pos = {220, 20};
    sfVector2f picture_pos = {400, 25};
    sfSprite *sprite;

    if (map->menu_pic) {
        sprite = sfSprite_create();
        sfSprite_setTexture(sprite, map->menu_pic, sfTrue);
        sfSprite_setPosition(sprite, picture_pos);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfSprite_destroy(sprite);
    }
    draw_title(window, &title_pos, map->font);
    draw_menu_button(window, map, &start_pos, "START");
    draw_menu_button(window, map, &load_pos, "LOAD");
    draw_menu_button(window, map, &exit_pos, "EXIT");
}

void determine_state(sfRenderWindow *window, sfVector2i *mouse_pos, map_t *map)
{
    if ((mouse_pos->y >= 20 && mouse_pos->y <= 80) &&
        (mouse_pos->x >= 20 && mouse_pos->x <= 110)) {
        map->state = GAME;
        return;
    }
    if ((mouse_pos->y >= 20 && mouse_pos->y <= 80) &&
        (mouse_pos->x >= 120 && mouse_pos->x <= 210)) {
        map->state = LOAD;
        return;
    }
    if ((mouse_pos->y >= 20 && mouse_pos->y <= 80) &&
        (mouse_pos->x >= 220 && mouse_pos->x <= 310)) {
        sfRenderWindow_close(window);
    }
}
