NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./minilibx
MLX = -L./minilibx -lmlx -framework OpenGL -framework AppKit
SRCS = main.c render.c events.c init_mlx.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
