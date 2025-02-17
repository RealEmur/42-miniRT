NAME = cub3D

LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a 

GNL_PATH = ./lib/gnl
GNL = $(GNL_PATH)/gnl.a

MLX_PATH = ./lib/mlx
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -L/usr/lib/x86_64-linux-gnu/ -lmlx -lXext -lX11 -lm -lz -I/usr/include/X11

HEADER_FILE = cub3d.h

HELPERS_PATH = ./helpers
HELPERS = $(HELPERS_PATH)/parser.c $(HELPERS_PATH)/validator.c $(HELPERS_PATH)/logger.c $(HELPERS_PATH)/keys.c $(HELPERS_PATH)/display.c $(HELPERS_PATH)/render.c $(HELPERS_PATH)/movement.c $(HELPERS_PATH)/cleaner.c

UTILS_PATH = ./utils

UTILS_PARSER_PATH = $(UTILS_PATH)/parser
UTILS_PARSER = $(UTILS_PARSER_PATH)/conversions.c $(UTILS_PARSER_PATH)/elements.c $(UTILS_PARSER_PATH)/map.c $(UTILS_PARSER_PATH)/floodfill.c 

UTILS_RENDER_PATH = $(UTILS_PATH)/render
UTILS_RENDER = $(UTILS_RENDER_PATH)/draw.c $(UTILS_RENDER_PATH)/texture.c

UTILS = $(UTILS_PARSER) $(UTILS_RENDER) $(UTILS_PATH)/strings.c $(UTILS_PATH)/timestamp.c

SOURCES = main.c $(UTILS) $(HELPERS)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(SOURCES) $(HEADER_FILE)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(SOURCES) $(LIBFT) $(GNL) $(MLX) $(MLX_FLAGS)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(GNL):
	make -C $(GNL_PATH)

$(MLX):
	curl -O https://cdn.intra.42.fr/document/document/28880/minilibx-linux.tgz
	tar -xvf minilibx-linux.tgz
	$(RM) $(MLX_PATH)
	mkdir -p $(MLX_PATH)
	mv minilibx-linux/* $(MLX_PATH)
	$(RM) minilibx-linux
	$(RM) minilibx-linux.tgz
	make -s -C $(MLX_PATH)

clean:
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(GNL_PATH)
	$(RM) $(MLX_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all
