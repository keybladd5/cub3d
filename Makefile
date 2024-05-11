# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 17:45:26 by ade-tole          #+#    #+#              #
#    Updated: 2024/05/11 17:45:28 by ade-tole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -MMD

MLX_F	=	-Iinclude -lglfw -framework Cocoa -framework OpenGL -framework IOKit

SRC		=	main.c draw.c

OBJ		=	$(SRC:.c=.o)

DEPS	=	$(SRC:.c=.d)

all		:	makelib $(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(FLAGS) MLX42/build/libmlx42.a $(MLX_F) $(OBJ) -o $(NAME)

%.o		:	%.c Makefile MLX42/build/libmlx42.a 
		$(CC) $(FLAGS) -c $< -o $@

makelib	:
		$(MAKE) -C MLX42/build/

clean	:
		rm -rf $(OBJ) $(DEPS)

fclean	:	clean
		$(MAKE) -C MLX42/build clean
		rm -f $(NAME)

re		:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re makelib