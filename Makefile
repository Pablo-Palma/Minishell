NAME = minishell
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc -I inc
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(SRC_DIR)main/main.c \
       $(SRC_DIR)main/minishell.c \
       $(SRC_DIR)execute/execute.c \
       $(SRC_DIR)shared/get_path.c \
       $(SRC_DIR)shared/command_split.c \
       $(SRC_DIR)signal/signal.c \
       $(SRC_DIR)builtins/handle_builtin.c \
       $(SRC_DIR)builtins/echo.c \
       $(SRC_DIR)builtins/cd.c \
       $(SRC_DIR)builtins/pwd.c \
       $(SRC_DIR)builtins/export.c

	   $(SRC_DIR)input/input.c	\
	   $(SRC_DIR)pipe/pipe.c

OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) -lreadline
	@echo "minishell compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
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
