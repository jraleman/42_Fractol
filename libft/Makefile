# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 23:46:05 by jaleman           #+#    #+#              #
#    Updated: 2016/11/14 19:52:47 by jaleman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME = libft.a

# Compiling flags
FLAGS = -Wall -Wextra -Werror

# Source files and object files
SRC = ft_memcpy.c ft_strequ.c ft_strcmp.c ft_str_to_lowcase.c ft_isupper.c \
		ft_itoa.c ft_puterror.c ft_putstr.c ft_putendl.c ft_strjoin.c \
		ft_strlen.c ft_strnew.c ft_strcpy.c ft_strcat.c ft_program_name.c \
		ft_strdup.c ft_strcap.c
OBJ = $(SRC:.c=.o)

# all rule
all: $(NAME)

%.o:%.c
	@gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "[INFO] Library [$(NAME)] created!"

# clean rule
clean:
	@rm -f $(OBJ)
	@echo "[INFO] Objects removed!"

# fclean rule
fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] Library [$(NAME)] removed!"

# re rule
re:	fclean all

# phony
.PHONY: all, clean, fclean, re
