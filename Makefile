NAME		= fdf
CC			= cc
CFLAGS		= -Wextra -Wall -Werror #-O0 -Ofast -g #-fsanitize=address -Wunreachable-code 
FT_PRINTF	= ./ft_printf
LIBFT		= ./libft
LIBMLX		= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)/include

LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw -pthread -lm #-L"/opt/homebrew/Cellar/glfw/3.4/lib/" #-ldl

SRCS	= fdf_utils.c transform_map_utils.c transform_map.c transform_image.c line.c colors_utils.c line_utils.c projection.c keyhook_utils.c keyhook_handler.c keyhook_handler_two.c keyhook.c parsing_utils.c parsing.c main.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(FT_PRINTF)/libftprintf.a:
	make -C $(FT_PRINTF)

$(LIBMLX)/build/libmlx42.a:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a $(LIBMLX)/build/libmlx42.a
	$(CC) $(OBJS) $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a  $(LIBS) -o $(NAME) 

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: re fclean clean all