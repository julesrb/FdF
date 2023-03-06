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

NAME	= libft.a

# -----------\ Directories \-------------------------------------------------- #

INC_DIREC = ./includes/
SRC_DIREC = sources/
OBJ_DIREC = objects/

# -----------\ Compilation \-------------------------------------------------- #

CC		= cc
CP		= cp -f 
RM		= rm
AR		= ar -rcs
MD		= -mkdir -p
CFLAGS	= -Wall -Werror -Wextra

# -----------\ Files & sources \---------------------------------------------- #

INCLUDES = -I $(INC_DIREC)

PRT_DIREC = prt/
PRT_FILES = ft_printf

GNL_DIREC = gnl/
GNL_FILES = get_next_line get_next_line_util

TO_DIREC = to/
TO_FILES = ft_atoi ft_itoa ft_tolower ft_toupper

IS_DIREC = is/
IS_FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint

MEM_DIREC = mem/
MEM_FILES = ft_bzero ft_calloc ft_memcmp ft_memcpy ft_memchr \
            ft_memmove ft_memset ft_memccpy

PUT_DIREC = put/
PUT_FILES = ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
			ft_putadd_fd ft_putnbr_uns_fd ft_puthex_fd

LST_DIREC = lst/
LST_FILES = ft_lstsize ft_lstadd_back ft_lstadd_front ft_lstiter \
			ft_lstdelone ft_lstclear ft_lstlast ft_lstnew ft_lstmap

STR_DIREC = str/
STR_FILES = ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
            ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
            ft_strnstr ft_strrchr ft_strtrim ft_substr

SRCS = $(addprefix $(SRC_DIREC), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIREC), $(addsuffix .o, $(SRC_FILES)))

SRC_FILES += $(addprefix $(TO_DIREC), $(TO_FILES))
SRC_FILES += $(addprefix $(IS_DIREC), $(IS_FILES))
SRC_FILES += $(addprefix $(PRT_DIREC), $(PRT_FILES))
SRC_FILES += $(addprefix $(GNL_DIREC), $(GNL_FILES))
SRC_FILES += $(addprefix $(MEM_DIREC), $(MEM_FILES))
SRC_FILES += $(addprefix $(PUT_DIREC), $(PUT_FILES))
SRC_FILES += $(addprefix $(LST_DIREC), $(LST_FILES))
SRC_FILES += $(addprefix $(STR_DIREC), $(STR_FILES))

# -----------\ Rules \-------------------------------------------------------- #

all:		DIR $(NAME)

$(NAME): $(OBJS)
				@$(AR) $(NAME) $(OBJS)
				@echo "- Library $(NAME) created !"

$(OBJ_DIREC)%.o : $(SRC_DIREC)%.c
				@$(CC) $(CFLAG) $(INCLUDES) -c $< -o $@ 
				@echo "- Compiled $<"

DIR:
				@$(MD) $(OBJ_DIREC)
				@$(MD) $(OBJ_DIREC)$(IS_DIREC)
				@$(MD) $(OBJ_DIREC)$(TO_DIREC)
				@$(MD) $(OBJ_DIREC)$(PRT_DIREC)
				@$(MD) $(OBJ_DIREC)$(GNL_DIREC)
				@$(MD) $(OBJ_DIREC)$(MEM_DIREC)
				@$(MD) $(OBJ_DIREC)$(PUT_DIREC)
				@$(MD) $(OBJ_DIREC)$(LST_DIREC)
				@$(MD) $(OBJ_DIREC)$(STR_DIREC)

clean :
				@$(RM) -rf $(OBJ_DIREC)
				@echo "- Deleted $(OBJ_DIREC) successfully"

fclean :		clean
				@$(RM) -f $(NAME)
				@echo "- Deleted $(NAME) successfully"

re:				fclean all

.PHONY: all clean fclean re
