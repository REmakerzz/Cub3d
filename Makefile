# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 11:05:29 by cmarchba          #+#    #+#              #
#    Updated: 2021/03/11 22:17:19 by cmarchba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

HEADER		= header/cub3d.h

MLX			= mlx_linux

SRC			= source/cub3d.c source/cub3d_tools.c source/cub3d_utils.c\
				source/get_next_line.c source/get_next_line_utils.c\
				source/init_player.c source/key_hook.c source/main_loop.c\
				source/map_validation.c source/parse.c source/parse_map.c\
				source/raycasting_utils.c source/screenshot_map.c\
				source/sprites.c source/parse_tools.c source/find_comma.c\

OBJS		= $(SRC:.c=.o)

CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
MLXFLAGS 	= -lmlx -lXext -lX11 -lm

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			make -C $(MLX)
			$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) mlx_linux/libmlx.a -L $(MLX) -o $(NAME)
			@echo "\n\033[0;32m$(NAME) successfully compiled\n"

clean:
			$(RM) $(OBJS)
			$(RM) screen.bmp
			make -C $(MLX) clean
			$(RM) $(NAME)

fclean:		clean

re:			fclean $(NAME)

.PHONY:		all clean fclean re

