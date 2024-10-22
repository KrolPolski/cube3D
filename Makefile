# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 15:24:40 by tparratt          #+#    #+#              #
#    Updated: 2024/10/22 12:03:46 by tparratt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

SRC		=	srcs/cast_wall.c \
			srcs/draw_2d_map.c \
			srcs/draw_squares.c \
			srcs/init_plyr.c \
			srcs/init_images.c \
			srcs/main.c \
			srcs/move_hooks.c \
			srcs/move_hooks2.c \
			srcs/parsing.c \
			srcs/parsing2.c \
			srcs/parsing3.c \
			srcs/parsing4.c \
			srcs/raycaster.c \
			srcs/raycaster2.c \
			srcs/raycaster_vertical.c \
			srcs/raycaster_horiz.c \
			srcs/setup_mlx.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/validation.c \
			srcs/validation2.c \
			srcs/walls.c
			
LIBFT		=	libft/libft.a

MLX42_DIR   = ./MLX42

ifeq ($(shell uname), Darwin)
	MLX42_LIBS = $(MLX42_DIR)/build/libmlx42.a -L"/opt/homebrew/opt/glfw/lib" -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else
MLX42_LIBS  = $(MLX42_DIR)/build/libmlx42.a -lglfw -ldl -pthread -lm
endif
OBJ			=	$(SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		= 	-Wextra -Wall -Werror

$(NAME):	$(OBJ)
			make -C ./libft
			cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
			make -C $(MLX42_DIR)/build -j4
			$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ) $(LIBFT) $(MLX42_LIBS)

all:		$(NAME)

clean:
			make clean -C libft
			${RM} $(OBJ)

fclean: 	clean
			make fclean -C libft
			${RM} $(NAME) ${OBJ}
			$(RM) -r $(MLX42_DIR)/build

re:			fclean all

.PHONY:		all clean fclean re

