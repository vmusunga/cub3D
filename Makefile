# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 12:31:33 by vmusunga          #+#    #+#              #
#    Updated: 2021/05/23 03:02:08 by vmusunga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=		get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				map.c \
				key_bindings.c \
				raycast.c \
				initialize.c \
				utils.c

INCLUDES	=	-I includes minilibx_mms_20200219

OBJS		=	$(SRCS:.c=.o)


#MAKE_LIBFT	=		@ cd libft && make ;
MLX			=		-Lmlx -lmlx -framework OpenGL -framework AppKit
CC			=		gcc

CFLAGS		=		-Wall -Werror -Wextra
RM			=		@rm -f
#BONUS		=
#OBJS_BONUS	=	$(BONUS:.c=.o)

NAME		=		cub3D

all:		$(NAME)

$(NAME):	#@$(MAKE_LIBFT)
			@$(CC) $(CFLAGS) $(MLX) $(SRCS) $(INCLUDES) -o $(NAME)



clean:
			#@cd libft && make clean

fclean:		clean
				@rm -rf cub3D
				#@cd libft && make fclean

re:			fclean all