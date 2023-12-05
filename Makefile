NAME = minishell
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc -I inc
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
SRC = main.c command_split.c get_path.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_LIB) -lreadline
	@echo "minishell compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "object files removed!"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "Executable and object files removed!"

re: fclean all
	@echo "Recompiled everything!"

.PHONY: all clean fclean re

