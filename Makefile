# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 00:40:45 by mkuida            #+#    #+#              #
#    Updated: 2025/08/31 17:55:57 by kosakats         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#			define:core														   #
# **************************************************************************** #

# **************************************************************************** #
#                                   Core                                       #
# **************************************************************************** #
NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRC_DIR = ./src
OBJ_DIR = ./obj

# Library
LIBFT_DIR = $(SRC_DIR)/libft_added_ftprintf
LIBFT     = $(LIBFT_DIR)/libft.a

# Includes & Flags
INCLUDES = -I includes -I $(LIBFT_DIR)/includes
LDFLAGS  = -L$(LIBFT_DIR)

# **************************************************************************** #
#                                Sources & Objects                             #
# **************************************************************************** #

# Main
SRC_MAIN      = main.c
SRCS_MAIN     = $(addprefix $(SRC_DIR)/, $(SRC_MAIN))
OBJS_MAIN     = $(SRCS_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Parser
SRC_PARSER    = parser.c \
                init_game.c \
                get_next_line/get_next_line.c \
                get_next_line/get_next_line_utils.c \
				ft_split.c

SRCS_PARSER   = $(addprefix $(SRC_DIR)/parser/, $(SRC_PARSER))
OBJS_PARSER   = $(SRCS_PARSER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# (Raycasterはコメントアウト中)
# SRCS_RAYCASTER = ...
# OBJS_RAYCASTER = ...

# Tie up
SRCS = $(SRCS_MAIN) $(SRCS_PARSER)
OBJS = $(OBJS_MAIN) $(OBJS_PARSER)

# **************************************************************************** #
#                                   Rules                                      #
# **************************************************************************** #
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compile rule with automatic directory creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

