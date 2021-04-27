# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 12:31:33 by vmusunga          #+#    #+#              #
#    Updated: 2021/04/27 17:13:39 by vmusunga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=		
INCLUDES	=	-I include
BONUS		=
OBJS		=	$(SRCS:.c=.o)
OBJS_BONUS	=	$(BONUS:.c=.o)

MAKE_LIBFT	=		@ cd libft && make ;
MLX			=		-lmlx -framework OpenGL -framework AppKit
CC			=		gcc

CFLAGS		=		-Wall -Werror -Wextra
RM			=		rm -f

NAME		=		cub3D

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -Imlx

$(NAME):	$(MAKE_LIBFT)
			$(CC) $(MLX) $(SRCS) $(INCLUDES) -o $(NAME)



clean:
			@cd libft && make clean
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			@cd libft && make fclean

re:			fclean all