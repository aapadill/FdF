NAME = FDF

CC = cc
CFLAGS = -Wall -Wextra -Werror -framework Cocoa -framework OpenGL -framework IOKit

SRC_SOURCES = main.c #\

SRC_OBJECTS = $(SRC_SOURCES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/"  -o $@

$(NAME): $(SRC_OBJECTS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $@ $^ ./libft/libft.a

clean:
	rm -f $(SRC_OBJECTS)
	$(MAKE) -C ./libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

