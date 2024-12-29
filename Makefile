NAME = miniRT

LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a 

GNL_PATH = ./lib/gnl
GNL = $(GNL_PATH)/gnl.a

MLX_PATH = ./lib/mlx
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

HELPERS_PATH = ./helpers
HELPERS = $(HELPERS_PATH)/parser.c $(HELPERS_PATH)/validator.c

UTILS_PATH = ./utils
UTILS_PARSER_PATH = $(UTILS_PATH)/parser
UTILS_PARSER = $(UTILS_PARSER_PATH)/conversions.c $(UTILS_PARSER_PATH)/objects.c $(UTILS_PARSER_PATH)/scene.c

UTILS = $(UTILS_PARSER) $(UTILS_PATH)/strings.c

SOURCES = main.c $(UTILS) $(HELPERS)

CC = cc 
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(SOURCES)
	$(CC) $(MLX_FLAGS) $(CFLAGS) $(SOURCES) $(LIBFT) $(GNL) $(MLX) -o $(NAME)

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

fclean: clean
	$(RM) $(NAME)

re: fclean all