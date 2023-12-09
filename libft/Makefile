NAME = libft.a
LIBFT_SRC_DIR = src
PRINTF_SRC_DIR = printf
GNL_SRC_DIR = get_next_line
OBJ_DIR = obj
INC_DIR = inc

LIBFT_SRC = $(addprefix $(LIBFT_SRC_DIR)/mand/, ft_atof.c ft_itoa.c \
	ft_puthexup_fd.c ft_strlcat.c ft_atoi.c ft_itoa_base.c ft_putnbr_fd.c \
	ft_strlcpy.c ft_bzero.c ft_itoa_baseup.c ft_putptr_fd.c ft_strlen.c \
	ft_calloc.c ft_memcmp.c ft_putstr_fd.c ft_strmapi.c \
	ft_free_arrays.c ft_memcpy.c ft_putunsigned_fd.c ft_strncmp.c \
	ft_isalnum.c ft_memchr.c ft_skip_space_sign.c ft_strnstr.c ft_isalpha.c \
	ft_memmove.c ft_split.c ft_strtrim.c ft_isascii.c ft_memset.c ft_strchr.c \
	ft_strrchr.c ft_isdigit.c ft_putchar_fd.c ft_strdup.c ft_substr.c \
	ft_isprint.c ft_putendl_fd.c ft_striteri.c ft_tolower.c ft_isspace.c \
	ft_puthexlo_fd.c ft_strjoin.c ft_toupper.c ft_isnumeric.c)

BONUS_SRC =	$(addprefix $(LIBFT_SRC_DIR)/bonus/, ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstmap_bonus.c ft_lstadd_front_bonus.c \
	ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c \
	ft_lstlast_bonus.c	ft_lstsize_bonus.c)

PRINTF_SRC = $(LIBFT_SRC_DIR)/printf/ft_printf.c
GNL_SRC = $(addprefix $(LIBFT_SRC_DIR)/get_next_line/, get_next_line.c get_next_line_utils.c \
	get_next_line_bonus.c get_next_line_utils_bonus.c)

SRC = $(LIBFT_SRC) $(PRINTF_SRC) $(GNL_SRC)
BONUS_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

FLAGS =	-Wall -Werror -Wextra -I$(INC_DIR)

.PHONY: all	clean	fclean	re	bonus

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Libft compiled succesfully!"

bonus: all $(BONUS_OBJ)
	@ar rcs $(NAME) $(BONUS) $(BONUS_OBJ)
	@echo "Libft bonus compiled succesfully!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@gcc $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(LIBFT_SRC_DIR)/mand $(OBJ_DIR)/$(LIBFT_SRC_DIR)/bonus $(OBJ_DIR)/$(PRINTF_SRC_DIR) $(OBJ_DIR)/$(GNL_SRC_DIR)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all
