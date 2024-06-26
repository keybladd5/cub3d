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

NAME	=	cub3D

CC		=	gcc

L_FLAGS =	-Wall -Wextra -Werror -MMD -g  -fsanitize=address

SRC	=	main.c draw.c render.c movement.c minimap.c dda_collission.c utils.c parse.c parse_mapdata.c parse_map.c \
		textures.c

OBJ		=	$(SRC:.c=.o)

DEPS	=	$(SRC:.c=.d)

MINILIBX_FOLDER ?= MLX42
MINILIBX_FILE ?= $(MINILIBX_FOLDER)/libmlx42.a
INCLUDE := include libft/include $(MINILIBX_FOLDER)/include
INCLUDE := $(addprefix -I,$(INCLUDE))

MLX_FLAGS := -O3 -ffast-math -funroll-loops -march=native -ldl -lglfw -lm

LIBFT_ROOT	:= libft/

LIB_A		:= $(LIBFT_ROOT)libft.a
HEADERS			:= $(MLX_H) cub3d.h libft/libft.h

#COLORES
GREEN		=	\033[38;5;154m
RED			=	\033[38;5;197m
PURPLE		=	\033[38;5;171m
BLUE		=	\033[38;5;14m
NC			=	\033[0m
YELLOW		=	\033[38;5;190m

all		:	makelib $(NAME)

$(NAME)	:	MLX42/build/libmlx42.a $(OBJ)
		@$(CC) $(L_FLAGS) $(OBJ) libft/libft.a MLX42/build/libmlx42.a -o $(NAME) $(MLX_FLAGS)
		@echo "${PURPLE}Cub3d binary Compiled${NC}"

%.o		:	%.c Makefile MLX42/build/libmlx42.a libft/libft.a cub3d.h
		@$(CC) $(L_FLAGS) $(INCLUDE) -c $< -o $@

makelib	:
		@echo "${BLUE}Compiling MLX42...${NC}"
		@(cd MLX42 >/dev/null && cmake -B build  >/dev/null && cmake --build build -j4 >/dev/null)
		@make -C MLX42/build -j4
		@echo "${GREEN}MLX42 Compiled${NC}"
		@echo "${BLUE}Compiling Libft...${NC}"
		@$(MAKE) -j -C libft/ & pid=$$!; \
		echo "."; \
		while ps -p $$pid > /dev/null; do \
			sleep 1; \
			echo "."; \
		done; 
		@echo "${GREEN}Libft Compiled${NC}"

clean	:
		@echo "${RED}Deleting objects and dependencies ${NC}"
		@rm -rf $(OBJ) $(DEPS)
		@$(MAKE) -j -C libft/ clean > /dev/null

fclean	:	clean
		@$(MAKE) -C MLX42/build clean -j > /dev/null
		@$(MAKE) -j -C libft/ fclean > /dev/null
		@echo "${RED}Deleting Cub3d binary ${NC}"
		@rm -f $(NAME)

re		:	fclean all

normi :
		@norminette cub3d.h dda_collission.c draw.c main.c minimap.c movement.c parse_map.c parse_mapdata.c parse.c render.c textures.c utils.c

-include $(DEPS)

.PHONY: all clean fclean re makelib normi
