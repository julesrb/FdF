# ------------- NAME --------------------------------------------------------- #
NAME = libft.a
# ------------- DIRECTORIES -------------------------------------------------- #
INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/
# ------------- COMPILATE ---------------------------------------------------- #
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
MD = mkdir -p
CP = cp -f 
# -------------- COLORS ------------------------------------------------------ #
GREEN=\033[0;32m
BLUE=\033[0;34m
ORANGE=\033[38;5;214m
RED=\033[0;31m
YELLOW = \033[0;33m
WHITE= \033[0;37m
# --------------- FILES / SOURCES --------------------------------------------- #
INCLUDE = -I $(INC_DIR)
IS_DIR = is/
IS_FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint
MEM_DIR = mem/
MEM_FILES = ft_bzero ft_calloc ft_memcmp ft_memcpy ft_memchr \
			ft_memmove ft_memset
PUT_DIR = put/
PUT_FILES = ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd 
STR_DIR = str/
STR_FILES = ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
			ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
			ft_strnstr ft_strrchr ft_strtrim ft_substr
TO_DIR = to/
TO_FILES = ft_atoi ft_itoa ft_tolower ft_toupper
SRC_FILES+=$(addprefix $(IS_DIR), $(IS_FILES))
SRC_FILES+=$(addprefix $(MEM_DIR), $(MEM_FILES))
SRC_FILES+=$(addprefix $(PUT_DIR), $(PUT_FILES))
SRC_FILES+=$(addprefix $(STR_DIR), $(STR_FILES))
SRC_FILES+=$(addprefix $(TO_DIR), $(TO_FILES))
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
# ------------ Rules ---------------------------------------------------------- #
all: DIR $(NAME)
$(NAME) : $(OBJS)
					@$(AR) $(NAME) $(OBJS)
					@echo "$(GREEN)\n ✓ Creado $(NAME)\n$(WHITE)"
%.o : $(SRC_DIR)%.c Makefile
				@$(MD) $(dir $@)
				@echo "$(ORANGE) Compilando  ➟  $(BLUE)$< $(WHITE)"
				@$(CC) -MT $@ -MMD -MP $(CFLAGS) $(INCLUDE) -c $< -o $@
DIR:
				@-mkdir -p $(OBJ_DIR)
				@-mkdir -p $(OBJ_DIR)$(IS_DIR)
				@-mkdir -p $(OBJ_DIR)$(MEM_DIR)
				@-mkdir -p $(OBJ_DIR)$(PUT_DIR)
				@-mkdir -p $(OBJ_DIR)$(STR_DIR) 
				@-mkdir -p $(OBJ_DIR)$(TO_DIR)
clean :
				@$(RM) -rf $(OBJ_DIR)
				@echo "$(RED)\n ✗ Archivos objetos libft borrados.‼️\n$(WHITE)";
fclean :        clean
				@$(RM) -f $(NAME)
				@echo "$(BLUE) Todo limpio...✌🏼$(WHITE)"
re:             fclean all
				@echo ""
				@echo "$(YELLOW) Borrado todo y recompilado...✌🏼$(WHITE)"
norm:
			@norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true
# Non-file targets
.PHONY: all clean fclean re norm