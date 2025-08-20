# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kotasakatsume <kotasakatsume@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 00:40:45 by mkuida            #+#    #+#              #
#    Updated: 2025/08/20 18:26:15 by kotasakatsu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#			define:core														   #
# **************************************************************************** #

# define core
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
OBJ_DIR = ./obj

#library
LIBFT_DIR = $(SRC_DIR)/libft_added_ftprintf
LIBFT = $(LIBFT_DIR)/libft.a

# MINILIBX_DIR = ./minilibx-linux
# MINILIBX = $(MINILIBX_DIR)/libmlx.a

#include(LDFLAG_kakuninhituyou)
#INCLUDES = -I includes -I $(MINILIBX_DIR) -I $(LIBFT_DIR)/includes
#LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -L/usr/local/lib -lXext -lX11 -lm

#kosakats test
INCLUDES = -I includes -I $(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)

# **************************************************************************** #
#			define:srcs&objs												   #
# **************************************************************************** #

#src_files
SRC_MAIN = main.c 
SRCS_MAIN = $(addprefix $(SRC_DIR)/, $(SRC_MAIN))
OBJS_MAIN = $(SRCS_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_PARSER = parser.c
SRC_PARSER_DIR = $(SRC_DIR)/parser
OBJ_PARSER_DIR = $(OBJ_DIR)/parser
SRCS_PARSER = $(addprefix $(SRC_PARSER_DIR)/, $(SRC_PARSER))
OBJS_PARSER = $(SRCS_PARSER:$(SRC_PARSER_DIR)/%.c=$(OBJ_PARSER_DIR)/%.o)

SRC_RAYCASTER =	set_test.c\
				set_mlx_hook.c\
				set_texture.c
SRC_RAYCASTER_DIR = $(SRC_DIR)/raycaster
OBJ_RAYCASTER_DIR = $(OBJ_DIR)/raycaster
SRCS_RAYCASTER = $(addprefix $(SRC_RAYCASTER_DIR)/, $(SRC_RAYCASTER))
OBJS_RAYCASTER = $(SRCS_RAYCASTER:$(SRC_RAYCASTER_DIR)/%.c=$(OBJ_RAYCASTER_DIR)/%.o)

#tie up
SRCS = $(SRCS_MAIN) $(SRCS_PARSER) $(SRCS_RAYCASTER)
OBJS = $(OBJS_MAIN) $(OBJS_PARSER) $(OBJS_RAYCASTER)

# **************************************************************************** #
#			define:action													   #
# **************************************************************************** #

#define
.PHONY: all clean fclean re

# defo
all: $(NAME)

# bild
$(NAME): $(MINILIBX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

# make obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# make obj file
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_PARSER_DIR)
	mkdir -p $(OBJ_RAYCASTER_DIR)

# build libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# MINILIBX
# $(MINILIBX):
# 	@if [ ! -d $(MINILIBX_DIR) ]; then \
# 		echo "MINILIBX not found. Cloning..."; \
# 		git clone https://github.com/42Paris/minilibx-linux.git $(MINILIBX_DIR); \
# 	fi
# 	@make -C $(MINILIBX_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -rf $(MINILIBX_DIR)

re: fclean all
