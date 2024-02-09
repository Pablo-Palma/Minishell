#!/bin/bash

allowed_functions=(
readline rl_clear_history rl_on_new_line
rl_replace_line rl_redisplay add_history
printf malloc free write access open read
close fork wait waitpid wait3 wait4 signal
sigaction kill exit getcwd chdir stat
lstat fstat unlink execve dup dup2 pipe
opendir readdir closedir strerror perror
isatty ttyname ttyslot ioctl getenv tcsetattr
tcgetattr tgetent tgetflag tgetnum tgetstr
tgoto tputs
)

# Ejecutar nm y filtrar por símbolos indefinidos
nm minishell | grep ' U ' | while read -r line; do
    # Extraer el nombre de la función, removiendo el prefijo "_"
    func=$(echo "$line" | awk '{print $2}' | sed 's/^_//')

    # Verificar si la función está en la lista de permitidas
    if ! printf '%s\n' "${allowed_functions[@]}" | grep -qx "$func"; then
        # Si la función no está permitida, buscar su ocurrencia en los archivos fuente
        echo "Función no permitida encontrada: $func"
        grep -rnw './src' -e "$func"
    fi
done
