# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 15:55:51 by ybouyzem          #+#    #+#              #
#    Updated: 2025/03/23 22:34:12 by ybouyzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



RAYCASTING = raycasting/raycasting.c raycasting/raycasting_utils.c \
             raycasting/move.c  raycasting/render_game.c  raycasting/render_utils.c \

GET_NEXT_LINE = parssing/get_line/get_line.c parssing/get_line/get_line_utils.c

PARSSING = parssing/parssing.c parssing/parssing_utils.c parssing/map_parssing1.c parssing/map_parssing2.c \
    parssing/parssing_utils2.c parssing/directions_parssing.c parssing/colors_parssing.c $(GET_NEXT_LINE) parssing/file_utils.c \
    parssing/put_textures.c

SRC_MANDATORY = main.c $(UTLS) $(RAYCASTING) $(PARSSING) garbage_collector.c 


FILESOURCE_LIBFT = ./libft/ft_isdigit.c ./libft/ft_split.c ./libft/ft_strlen.c  \
    ./libft/ft_atoi.c ./libft/ft_strchr.c ./libft/ft_strdup.c  \
    ./libft/ft_calloc.c ./libft/ft_isalnum.c ./libft/ft_strjoin.c ./libft/ft_strrchr.c \
    ./libft/ft_isalpha.c ./libft/ft_strtrim.c ./libft/ft_bzero.c ./libft/ft_strlcpy.c\
    ./libft/ft_putstr_fd.c ./libft/ft_strlcat.c\

FILESOURCE = $(SRC_MANDATORY) $(FILESOURCE_LIBFT)

OBJ = $(FILESOURCE:%.c=%.o)

LIBS = MLX42/libglfw3.a MLX42/libmlx42.a
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit $(LIBS)

PROGRAM = cub3D

CC = cc
FLAGS = -Wall -Werror -Wextra -O3 -ffast-math

$(PROGRAM): $(OBJ)
	$(CC) $(FLAGS) $(MLXFLAGS) $(OBJ) -o $(PROGRAM)

%.o: %.c include/cub.h ./libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

all: $(PROGRAM)


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PROGRAM)

re: fclean all

.PHONY: clean 
