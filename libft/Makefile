# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 22:54:20 by fiaparec          #+#    #+#              #
#    Updated: 2022/04/02 11:55:08 by fiaparec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc

CC_FLAGS		= -Wall -Wextra -Werror

AR				= ar rcs

RM				= rm -f

SRCS			=	ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c \
					ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
					ft_tolower.c ft_toupper.c \
					ft_atoi.c ft_itoa.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
					ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
					ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
					ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
					get_next_line.c get_next_line_utils.c \
					ft_printf.c ft_printf_identifiers.c ft_printf_handlers.c \
					ft_printf_c.c ft_printf_s.c ft_printf_p.c \
					ft_printf_d.c ft_printf_i.c ft_printf_u.c \
					ft_printf_u.c ft_printf_x.c ft_printf_uppx.c \
					ft_printf_percent.c \
					ft_printf_utils.c

OBJS			= $(SRCS:.c=.o)

NAME			= libft.a

.c.o:
				$(CC) $(CC_FLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(AR) $(NAME) $(OBJS)

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)
				$(RM) *.out
				$(RM) *.a

re:				fclean all

.PHONY:			all clean fclean re
