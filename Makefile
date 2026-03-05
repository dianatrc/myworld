##
## EPITECH PROJECT, 2026
## MY_WORLD
## File description:
## Makefile for building the my_world project
##

CC = epiclang
LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm
CFLAGS = -Wall -Wextra -Werror -I.

SRC = src/main.c \
	src/window.c \
	src/map.c \
	src/iso_proj.c \
	src/tools.c \
	src/toolbar.c \
	src/menu.c \
	src/camera.c \
	src/file.c
OBJ = $(SRC:.c=.o)

all: my_world

my_world: $(OBJ)
	$(CC) -o my_world $(OBJ) $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f my_world

re: fclean all

.PHONY: all clean fclean re
