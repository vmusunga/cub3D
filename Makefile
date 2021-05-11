# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 12:31:33 by vmusunga          #+#    #+#              #
#    Updated: 2021/05/11 17:38:14 by vmusunga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=		get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				libft/libft.a \
				map.c


#SRCS	=		map.c
				#hooking.c
				#window.c

INCLUDES	=	-I includes
BONUS		=
OBJS		=	$(SRCS:.c=.o)
#OBJS_BONUS	=	$(BONUS:.c=.o)

MAKE_LIBFT	=		@ cd libft && make ;
MLX			=		-lmlx -framework OpenGL -framework AppKit
CC			=		gcc

CFLAGS		=		-Wall -Werror -Wextra
RM			=		rm -f

NAME		=		cub3D

all:		$(NAME)

$(NAME):	@$(MAKE_LIBFT)
			@$(CC) $(CFLAGS) $(MLX) $(SRCS) $(INCLUDES) -o $(NAME)



clean:
			@cd libft && make clean

fclean:		clean
				@rm -rf cub3D
				@cd libft && make fclean

re:			fclean all