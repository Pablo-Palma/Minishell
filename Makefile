# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 19:40:56 by jbaeza-c          #+#    #+#              #
#    Updated: 2023/12/05 20:09:56 by jbaeza-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nombre
NAME = minishell

#Compilación
CC = cc 
CFLAGS = -Wall -Wextra -Werror

#Directorios
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
INC_DIR		= ./inc/
LIBFT_DIR	= ./libft/

#Files
SRC_FILES	= main.c
OBJ_FILES	= $(SRC_FILES:.c=.o)

#Direcciones
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT		= $(addprefix $(LIBFT_DIR), libft.a)

#Ejecutable
all: obj $(NAME)

#Gestión de los objetos
obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

#Compilación de los objetos con las librerías
$(NAME): $(OBJ) $(LIBFT)
	@echo "Compilando..."
	$(CC) $(OBJ) -o $(NAME) $(LIBFT)
	@echo "Completado!"

#Compilación de la librería
$(LIBFT):
	make -C $(LIBFT_DIR) all

#Eliminación de los objetos
clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)
	@echo "Object removed."

#Eliminación de los objetos y los ejecutables
fclean: clean
	make -C $(LIBFT:DIR) fclean
	$(RM) $(NAME)
	@echo "Everything has been removed."

#re-make
re: fclean all

.PHONY: all clean fclean re