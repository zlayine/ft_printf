# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:42:57 by zlayine           #+#    #+#              #
#    Updated: 2019/11/23 21:50:49 by zlayine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf.c \
		srcs/chars_manager.c \
		srcs/digits_manager.c \
		srcs/flags_manager.c \
		srcs/ft_utils.c \
		srcs/hex_helper.c \
		srcs/flags_setters.c
LIB_SRC = ./libft/ft_atoi.c \
		./libft/ft_bzero.c \
		./libft/ft_calloc.c \
		./libft/ft_isalnum.c \
		./libft/ft_isalpha.c \
		./libft/ft_isascii.c \
		./libft/ft_isdigit.c \
		./libft/ft_isprint.c \
		./libft/ft_itoa.c \
		./libft/ft_memccpy.c \
		./libft/ft_memchr.c \
		./libft/ft_memcmp.c \
		./libft/ft_memcpy.c \
		./libft/ft_memmove.c \
		./libft/ft_memset.c \
		./libft/ft_putchar_fd.c \
		./libft/ft_putendl_fd.c \
		./libft/ft_putnbr_fd.c \
		./libft/ft_putstr_fd.c \
		./libft/ft_split.c \
		./libft/ft_strchr.c \
		./libft/ft_strdup.c \
		./libft/ft_strjoin.c \
		./libft/ft_strlcat.c \
		./libft/ft_strlcpy.c \
		./libft/ft_strlen.c \
		./libft/ft_strmapi.c \
		./libft/ft_strncmp.c \
		./libft/ft_strnstr.c \
		./libft/ft_strrchr.c \
		./libft/ft_strtrim.c \
		./libft/ft_substr.c \
		./libft/ft_tolower.c \
		./libft/ft_toupper.c \
		./libft/ft_pow.c \
		./libft/ft_putnbr.c \
		./libft/ft_putstr.c \
		./libft/ft_putchar.c \
		./libft/ft_hex_digit.c \
		./libft/ft_nblen.c \
		./libft/ft_nblen_un.c \
		./libft/ft_putnbr_un.c
OBJ = $(SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)
INC = includes

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIB_OBJ) $(OBJ) $(INC)/libft.h $(INC)/ft_printf.h
	ar rc $(NAME) $(LIB_OBJ) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@ -I $(INC)

clean:
	rm -rf $(LIB_OBJ)
	rm -rf $(OBJ)

fclean: clean
	rm -rf libftprintf.a

re: fclean all
