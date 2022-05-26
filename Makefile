# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 19:07:19 by fiaparec          #+#    #+#              #
#    Updated: 2022/05/26 07:16:26 by fiaparec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc

CC_FLAGS		= -Wall -Wextra -Werror

MLX_FLAGS		= -lmlx -lXext -lX11

AR				= ar rcsv

RM				= rm -f

LIBFT_HEADER	= -I libft

LIBFT_LIB		= libft/libft.a

LIBFT_LIB_LINK	= -L libft -l:libft.a

SRCS			=	so_long.c

OBJS			= $(SRCS:.c=.o)

NAME			= so_long

.c.o:
				$(CC) $(CC_FLAGS) $(LIBFT_HEADER) -c $< -o $(<:.c=.o)

$(NAME):		$(LIBFT_LIB) $(OBJS)
				$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT_LIB_LINK) $(MLX_FLAGS) -o $(NAME)

$(LIBFT_LIB):
				make -C libft

all:			$(NAME)

clean:			
				make clean -C libft
				$(RM) $(OBJS)

fclean:			clean
				make fclean -C libft
				$(RM) $(NAME)
				$(RM) *.out
				$(RM) *.a

re:				fclean all

.PHONY:			all clean fclean re
