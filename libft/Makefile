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

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
AR		= ar
ARFLAGS	= -rcs
RM		= rm
RMFLAGS	= -rf

# HEADERS
INCLUDES = -I$(HEADERS_DIRECTORY)
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = libft.h

# SOURCES
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = ./char_operation/ft_isalnum.c \
				./char_operation/ft_isascii.c \
				./char_operation/ft_isprint.c \
				./char_operation/ft_toupper.c \
				./char_operation/ft_isalpha.c \
				./char_operation/ft_isdigit.c \
				./char_operation/ft_tolower.c \
				./get_next_line/get_next_line.c \
				./get_next_line/get_next_line_util.c \
				./linked_list/ft_lstadd_back.c \
				./linked_list/ft_lstclear.c \
				./linked_list/ft_lstiter.c \
				./linked_list/ft_lstmap.c \
				./linked_list/ft_lstsize.c \
				./linked_list/ft_lstadd_front.c \
				./linked_list/ft_lstdelone.c \
				./linked_list/ft_lstlast.c \
				./linked_list/ft_lstnew.c \
				./memory_manipulation/ft_bzero.c \
				./memory_manipulation/ft_memccpy.c \
				./memory_manipulation/ft_memcmp.c \
				./memory_manipulation/ft_memmove.c \
				./memory_manipulation/ft_calloc.c \
				./memory_manipulation/ft_memchr.c \
				./memory_manipulation/ft_memcpy.c \
				./memory_manipulation/ft_memset.c \
				./string_manipulation/ft_split.c \
				./string_manipulation/ft_striteri.c \
				./string_manipulation/ft_strlcpy.c \
				./string_manipulation/ft_strncmp.c \
				./string_manipulation/ft_strtrim.c \
				./string_manipulation/ft_strchr.c \
				./string_manipulation/ft_strjoin.c \
				./string_manipulation/ft_strlen.c \
				./string_manipulation/ft_strnstr.c \
				./string_manipulation/ft_substr.c \
				./string_manipulation/ft_strdup.c \
				./string_manipulation/ft_strlcat.c \
				./string_manipulation/ft_strmapi.c \
				./string_manipulation/ft_strrchr.c \
				./var_convetion/ft_atoi.c \
				./var_convetion/ft_itoa.c \
				./write_and_print/ft_printf.c \
				./write_and_print/ft_putchar_fd.c \
				./write_and_print/ft_puthex_fd.c \
				./write_and_print/ft_putnbr_uns_fd.c \
				./write_and_print/ft_putadd_fd.c \
				./write_and_print/ft_putendl_fd.c \
				./write_and_print/ft_putnbr_fd.c \
				./write_and_print/ft_putstr_fd.c \

# OBJECTS
OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLOR FLAGS
CLR_BLACK   = \033[0;30m
CLR_RED		= \033[0;31m
CLR_GREEN	= \033[0;32m
CLR_LBLUE   = \033[0;94m
CLR_YELLOW  = \033[0;33m
CLR_MAGENTA = \033[0;35m
CLR_RESET	= \033[0m

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(CLR_GREEN)objects were created$(CLR_RESET)"
	@echo "$(NAME): $(CLR_GREEN)$(NAME) was created$(CLR_RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(CLR_GREEN)$(OBJECTS_DIRECTORY) was created$(CLR_RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(CLR_GREEN).$(CLR_RESET)\c"

clean:
	@$(RM) $(RMFLAGS) $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(CLR_RED)$(OBJECTS_DIRECTORY) was deleted$(CLR_RESET)"
	@echo "$(NAME): $(CLR_RED)objects were deleted$(CLR_RESET)"

fclean: clean
	@$(RM) $(RMFLAGS) $(NAME)
	@echo "$(NAME): $(CLR_RED)$(NAME) was deleted$(CLR_RESET)"

re: fclean all

.PHONY: all clean fclean re
