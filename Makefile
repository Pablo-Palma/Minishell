NAME = minishell
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc -I inc
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
<<<<<<< HEAD
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
=======
OBJ_DIR = obj/

# Lista de todos los archivos fuente
SRCS = $(SRC_DIR)main/main.c \
       $(SRC_DIR)main/minishell.c \
       $(SRC_DIR)execute/execute.c \
       $(SRC_DIR)shared/get_path.c \
       $(SRC_DIR)shared/command_split.c
       # Agrega aquí más archivos si los tienes

# Convertir archivos fuente a sus correspondientes archivos objeto
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) -lreadline
	@echo "minishell compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
>>>>>>> Pablo
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
<<<<<<< HEAD

=======
>>>>>>> Pablo
