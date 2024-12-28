NAME = miniRT

LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a 

GNL_PATH = ./lib/gnl
GNL = $(GNL_PATH)/gnl.a

HELPERS_PATH = ./helpers
HELPERS = $(HELPERS_PATH)/parser.c $(HELPERS_PATH)/validator.c

UTILS_PATH = ./utils
UTILS_PARSER_PATH = $(UTILS_PATH)/parser
UTILS_PARSER = $(UTILS_PARSER_PATH)/conversions.c $(UTILS_PARSER_PATH)/objects.c $(UTILS_PARSER_PATH)/scene.c

UTILS = $(UTILS_PARSER) $(UTILS_PATH)/strings.c

SOURCES = main.c $(UTILS) $(HELPERS)

CC = cc 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBFT) $(GNL) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(GNL):
	make -C $(GNL_PATH)

clean:
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(GNL_PATH) 

fclean: clean
	$(RM) $(NAME)

re: fclean all