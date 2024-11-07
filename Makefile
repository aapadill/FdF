NAME		= fdf
CC			= cc
CFLAGS		= -Wextra -Wall -Werror -O2 -Ofast -g #-fsanitize=address -Wunreachable-code 
FT_PRINTF	= ./ft_printf
LIBFT		= ./libft
LIBMLX		= ./MLX42

HEADERS	= -Iincludes -I $(LIBMLX)/include

LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw -pthread -lm #-L"/opt/homebrew/Cellar/glfw/3.4/lib/" #-ldl

SOURCES = srcs/fdf_utils.c \
			srcs/transform_map_utils.c \
			srcs/transform_map.c \
			srcs/transform_image.c \
			srcs/line.c \
			srcs/colors_utils.c \
			srcs/line_utils.c \
			srcs/projection.c \
			srcs/keyhook_utils.c \
			srcs/keyhook_handler.c \
			srcs/keyhook_handler_two.c \
			srcs/keyhook.c \
			srcs/parsing_utils.c \
			srcs/parsing.c \
			srcs/main.c

OBJS	= $(SOURCES:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	make -C $(LIBFT)
	make bonus -C $(LIBFT)

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
