NAME = minishell 
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc -I inc
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
OBJ_DIR = obj/

SRCS =	$(SRC_DIR)aux_ft/array_size.c			\
		$(SRC_DIR)aux_ft/cmd_split.c			\
		$(SRC_DIR)aux_ft/env_utils.c			\
		$(SRC_DIR)aux_ft/ft_strncpy.c			\
		$(SRC_DIR)aux_ft/ft_strndup.c			\
    	$(SRC_DIR)aux_ft/get_path.c				\
		$(SRC_DIR)aux_ft/here_doc_env.c			\
		$(SRC_DIR)aux_ft/input_split.c			\
		$(SRC_DIR)aux_ft/quotes.c				\
		$(SRC_DIR)aux_ft/utils.c				\
    	$(SRC_DIR)builtins/cd.c					\
    	$(SRC_DIR)builtins/echo.c				\
		$(SRC_DIR)builtins/env.c				\
		$(SRC_DIR)builtins/exit.c				\
    	$(SRC_DIR)builtins/export.c				\
    	$(SRC_DIR)builtins/handle_builtin.c		\
    	$(SRC_DIR)builtins/pwd.c				\
		$(SRC_DIR)builtins/unset.c				\
		$(SRC_DIR)execute/execute_utils.c 		\
    	$(SRC_DIR)execute/execute.c 			\
		$(SRC_DIR)execute/heredoc.c				\
		$(SRC_DIR)execute/pipe_utils_2.c		\
		$(SRC_DIR)execute/pipe_utils.c			\
		$(SRC_DIR)execute/pipe.c				\
		$(SRC_DIR)execute/programs.c			\
		$(SRC_DIR)execute/redirect.c			\
		$(SRC_DIR)input/ast_node.c				\
		$(SRC_DIR)input/ast_utils.c				\
		$(SRC_DIR)input/ast.c					\
		$(SRC_DIR)input/envp.c					\
		$(SRC_DIR)input/input.c					\
		$(SRC_DIR)input/lexer.c 				\
		$(SRC_DIR)input/token.c 				\
		$(SRC_DIR)main/main.c 					\
    	$(SRC_DIR)main/minishell.c				\
    	$(SRC_DIR)signal/signal.c 				\
		$(SRC_DIR)signal/signal_2.c 			\
		$(SRC_DIR)bonus/wildcards_2.c			\
		$(SRC_DIR)bonus/wildcards.c

OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) -lreadline
	@echo "minishell compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
