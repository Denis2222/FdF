.PHONY: libft

SRCS = map.c \
	   display.c \
	   read.c \
	   setup.c \
	   t_dot.c \
	   t_wire.c \
	   key.c \
	   t_cam.c \
	   main.c

NAME = fdf
GCC_FLAG = -Wall -Werror -Wextra
CC = gcc $(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft mlx $(NAME)
	./fdf ./map/42.fdf

libft:
	make -C ./libft/

mlx:
	make -C ./minilibx/
	cp ./minilibx/libmlx.a ./

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lminilibx/ -lmlx -framework OPENGL -framework Appkit -Llibft -lft

clean:
	rm -f $(NAME)
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	make -C minilibx/ clean

re: fclean all
