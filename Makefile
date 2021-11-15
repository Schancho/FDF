
NAME = fdf

MLX = minilibx_macos/libmlx.a 

SRC = *.c  utils/*.c

CC = gcc -Wall -Wextra -Werror -g3 -fsanitize=address

all	:	$(NAME)

$(MLX) :
	@make -C minilibx_macos/  

$(NAME) :	$(SRC) $(MLX)
	@$(CC) -o $(NAME) $(SRC) $(MLX) -framework OpenGL -framework AppKit 

clean : 
	rm fdf
	@make clean -C minilibx_macos/
	
re : clean all
