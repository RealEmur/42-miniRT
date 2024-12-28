NAME = miniRT
SOURCES = main.c
CC = cc 
CLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a 

GNL_PATH = ./lib/gnl
GNL = $(GNL_PATH)/gnl.a

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