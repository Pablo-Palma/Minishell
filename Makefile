# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 19:40:56 by jbaeza-c          #+#    #+#              #
#    Updated: 2023/12/05 20:58:34 by jbaeza-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc -I inc
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRC = $(addprefix $(SRC:DIR), $(SRCS))

SRCS = main.c command_split.c get_path.c minishell.c

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