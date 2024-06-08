# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 13:52:10 by polmarti          #+#    #+#              #
#    Updated: 2023/10/06 10:16:56 by polmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_calloc.c \
	   ft_isdigit.c \
	   ft_isspace.c \
	   ft_memcpy.c \
	   ft_strdup.c \
	   ft_strlen.c \
	   ft_strtrim.c \
	   ft_isalnum.c \
	   ft_isprint.c \
	   ft_memmove.c \
	   ft_strjoin.c \
	   ft_strncmp.c \
	   ft_strxcmp.c \
	   ft_substr.c \
	   ft_atoi.c \
	   ft_isalpha.c \
	   ft_memchr.c \
	   ft_memset.c \
	   ft_strlcat.c \
	   ft_strnstr.c \
	   ft_tolower.c \
	   ft_bzero.c \
	   ft_isascii.c \
	   ft_memcmp.c \
	   ft_strchr.c \
	   ft_strlcpy.c \
	   ft_strrchr.c \
	   ft_toupper.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_strjoin_free.c \
	   gnl/get_next_line.c \
	   gnl/get_next_line_utils.c \
	   printf/ft_printf.c \
	   printf/ft_printf_utils.c

SRCS_BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c
FLAGS = -Wall -Wextra -Werror -MMD
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
BONUS = .bonus
all: $(NAME)
CC = gcc

%.o:%.c Makefile
	@$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
bonus: $(BONUS)
	
$(BONUS): $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	touch $@
clean:
	@rm -f $(OBJS) $(OBJS_BONUS) $(DEPS) $(DEPS_BONUS)
fclean: clean
	@rm -f $(NAME)
re: fclean all
-include $(DEPS)
-include $(DEPS_BONUS)
.PHONY: all clean fclean re bonus
