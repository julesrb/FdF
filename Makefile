# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubernar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 15:34:46 by jubernar          #+#    #+#              #
#    Updated: 2023/02/27 15:34:48 by jubernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------\ Name \--------------------------------------------------------- #

NAME	= fdf

# -----------\ Directories \-------------------------------------------------- #

INC_DIREC = ./includes/
SRC_DIREC = ./sources/
OBJ_DIREC = ./objects/
LIBFT_DIR = ./lib/libft/
LIBMLX_DIR = ./lib/MLX42

# -----------\ Compilation \-------------------------------------------------- #

CC		= cc
AR		= ar -rcs
MD		= -mkdir -p
CFLAGS	= -Wall -Werror -Wextra

# -----------\ Files & sources \---------------------------------------------- #

INCLUDES = -I $(INC_DIREC) -I $(LIBFT_DIR)inc -I $(LIBMLX_DIR)inc

SRC_FILES = test

SRCS = $(addprefix $(SRC_DIREC), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIREC), $(addsuffix .o, $(SRC_FILES)))

# -----------\ Rules \-------------------------------------------------------- #

all: libmlx libft $(NAME)

libmlx:
				@git clone https://github.com/codam-coding-college/MLX42.git ./lib/MLX42
				@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

libft:
				@$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(OBJ_DIREC) $(OBJS) 
				@$(CC) $(CFLAGS) $(LIBRARIE)
				@echo "- Library $(NAME) created !"

$(OBJ_DIREC)%.o : $(SRC_DIREC)%.c
				@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
				@echo "- Compiled $<"

$(OBJ_DIREC):
				@$(MD) $(OBJ_DIREC)
				@echo "- Created folder $(OBJ_DIREC)"

clean :
				@rm -fr $(LIBMLX_DIR)/build
				@echo "- Deleted $(OBJ_DIREC) successfully"

fclean :		clean
				
			rm -fr $(LIBMLX_DIR)
				@echo "- Deleted $(NAME) successfully"

re:				fclean all

.PHONY: all clean fclean re
