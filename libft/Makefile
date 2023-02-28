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
SOURCES_LIST = ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_toupper.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_tolower.c \
				get_next_line.c \
				get_next_line_util.c \
				ft_lstadd_back.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstsize.c \
				ft_lstadd_front.c \
				ft_lstdelone.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_bzero.c \
				ft_memccpy.c \
				ft_memcmp.c \
				ft_memmove.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcpy.c \
				ft_memset.c \
				ft_split.c \
				ft_striteri.c \
				ft_strlcpy.c \
				ft_strncmp.c \
				ft_strtrim.c \
				ft_strchr.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strnstr.c \
				ft_substr.c \
				ft_strdup.c \
				ft_strlcat.c \
				ft_strmapi.c \
				ft_strrchr.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_printf.c \
				ft_putchar_fd.c \
				ft_puthex_fd.c \
				ft_putnbr_uns_fd.c \
				ft_putadd_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \

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

$(OBJECTS_DIRECTORY)%.o:		%.c libft.h
			@mkdir -p objs/
			@echo "Compiling: $<"
			@${CC} -c -o $@ $< ${CFLAGS} 

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
