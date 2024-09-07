#relinking /build when make all many timesi, what the fuck with the naming? libftt, ft_printff (i did it because it wasnt working otherwise)

NAME		= fdf
CC			= cc
CFLAGS		= -Wextra -Wall -Werror -g #-fsanitize=address -Wunreachable-code -Ofast
FT_PRINTF	= ./ft_printf
LIBFT		= ./libft
LIBMLX		= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)/include

LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/" -pthread -lm #ldl

SRCS	= fdf_utils.c map_parsing.c main.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

ft_printff:
	make -C $(FT_PRINTF)

libftt:
	make -C $(LIBFT)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): libftt ft_printff libmlx $(OBJS)
	$(CC) $(OBJS) $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a  $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: re, fclean, clean, libmlx, ft_printff, libftt
