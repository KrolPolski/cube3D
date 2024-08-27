# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 15:24:40 by tparratt          #+#    #+#              #
#    Updated: 2024/08/26 15:25:48 by tparratt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

SRC			=	srcs/main.c \
					srcs/validation.c \
					srcs/utils.c \
					srcs/parsing.c \

LIBFT		=	libft/libft.a

MLX42_DIR   = ./MLX42
MLX42_LIBS  = $(MLX42_DIR)/build/libmlx42.a -lglfw -ldl -pthread -lm

OBJ			=	$(SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		= -Wextra -Wall -Werror

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

