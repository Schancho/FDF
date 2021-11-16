# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schancho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 08:10:07 by schancho          #+#    #+#              #
#    Updated: 2021/11/16 08:10:50 by schancho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fdf

MLX = minilibx_macos/libmlx.a 

SRC = *.c  utils/*.c

CC = gcc -Wall -Wextra -Werror -g3 #-fsanitize=address

all	:	$(NAME)

$(MLX) :
	@make -C minilibx_macos/  

$(NAME) :	$(SRC) $(MLX)
	@$(CC) -o $(NAME) $(SRC) $(MLX) -framework OpenGL -framework AppKit 

clean : 
	rm fdf
	@make clean -C minilibx_macos/
fclean :
	@rm -rf fdf
	
re : clean all
