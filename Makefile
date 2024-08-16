NAME	= FDF
CFLAGS	= -Wextra -Wall -Werror #-Wunreachable-code -Ofast
LIBFT	= ./libft
LIBMLX	= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/" #-ldl -pthread -lm
SRCS	= example.c
OBJS	= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

libft:
	make -C $(LIBFT)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	make -C $(LIBFT) fclean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
