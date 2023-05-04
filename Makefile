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

INC_DIREC = includes/
SRC_DIREC = sources/
OBJ_DIREC = objects/
LIBFT_DIR = lib/libft/
LIBMLX_DIR = lib/MLX42/

# -----------\ Compilation \-------------------------------------------------- #

CC		= cc 
AR		= ar -rcs
MD		= -mkdir -p
CFLAGS	= -Wall -Werror -Wextra

# -----------\ Files & sources \---------------------------------------------- #

INCS = -I $(INC_DIREC) -I $(LIBFT_DIR)includes/ -I $(LIBMLX_DIR)include/MLX42/

#- for linux -#
#LIBS = $(LIBFT_DIR)libft.a \
		$(LIBMLX_DIR)build/libmlx42.a -ldl -lglfw -pthread -lm

#- for mac -#
LIBS = $(LIBMLX_DIR)/build/libmlx42.a -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" \
		$(LIBFT_DIR)libft.a

SRC_FILES = main \
			draw \
			parse \
			color \
			line_up \
			line_down \
			map_size \
			keyhook

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
				$(CC) -g $(CFLAGS) $(OBJS) $(LIBS) $(INCS) -o $(NAME) -g
				@echo "- Library $(NAME) created !"

$(OBJ_DIREC)%.o : $(SRC_DIREC)%.c
				@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
				@echo "- Compiled $<"

$(OBJ_DIREC):
				@$(MD) $(OBJ_DIREC)
				@echo "- Created folder $(OBJ_DIREC)"

clean :
				@$(MAKE) -sC $(LIBFT_DIR) clean
				@echo "- Deleted $(LIBFT_DIR) successfully"
				@rm -f $(LIBMLX)/build
				@echo "- Deleted $(LIBMLX) successfully"
				@rm -fr $(OBJS)
				@echo "- Deleted $(OBJS) successfully"

fclean :		clean
				
				@rm -fr $(LIBMLX_DIR)
				@echo "- Deleted $(LIBMLX_DIR) successfully"
				@rm -fr $(LIBFT_DIR)libft.a
				@echo "- Deleted libft.a successfully"
				@rm -fr fdf
				@echo "- Deleted fdf successfully"

re:				fclean all

.PHONY: all clean fclean re
