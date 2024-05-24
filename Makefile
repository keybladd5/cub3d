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

FLAGS	=	-Wall -Wextra -Werror -MMD -g -fsanitize=address

MLX_F	=	-Iinclude -lglfw -framework Cocoa -framework OpenGL -framework IOKit

SRC		=	main.c draw.c render.c

OBJ		=	$(SRC:.c=.o)

DEPS	=	$(SRC:.c=.d)

LIBFT_ROOT	:= libft/

LIB_A		:= $(LIBFT_ROOT)libft.a

#COLORES
GREEN		=	\033[38;5;154m
RED			=	\033[38;5;197m
PURPLE		=	\033[38;5;171m
BLUE		=	\033[38;5;14m
NC			=	\033[0m
YELLOW		=	\033[38;5;190m

all		:	makelib $(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(FLAGS) libft/libft.a MLX42/build/libmlx42.a $(MLX_F) $(OBJ) -o $(NAME)

%.o		:	%.c Makefile MLX42/build/libmlx42.a libft/libft.a cub3d.h
		$(CC) $(FLAGS) -c $< -o $@

makelib	:
		$(MAKE) -C MLX42/build/
		@echo "${BLUE}Compiling Libft...${NC}"
		@$(MAKE) -j -C libft/ & pid=$$!; \
		echo "."; \
		while ps -p $$pid > /dev/null; do \
			sleep 1; \
			echo "."; \
		done; 
		@echo "${GREEN}Libft Compiled${NC}"

clean	:
		rm -rf $(OBJ) $(DEPS)
		@$(MAKE) -j -C libft/ clean

fclean	:	clean
		$(MAKE) -C MLX42/build clean
		@$(MAKE) -j -C libft/ fclean
		rm -f $(NAME)

re		:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re makelib