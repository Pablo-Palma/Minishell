/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:29:14 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/06 15:51:27 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
/*
La salida de esta funcion haría de entrada en is_non_pipe_cmd()
Quiere decir, el comando pasaria por esta funcion para mandarla a la comprobación 
de comandos y dictaminar si es un comando que requiere el uso de pipe o no.
Los comandos cd, export, unset y exit no generan ninguna salida por lo que no 
siren como comando de entrada en pipes. (Creo)
*/

/*
Esta funcion elimina las comillas en una cadena, siempre y cuando sean comillas usadas
como metacaracter y no como caracter.
EJEMPLOS:
"Hola" ---> Hola
"Hola 'mundo'" ---> Hola 'mundo'
'Hola "mundo"' ---> Hola "mundo"
*/
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		simples;
	int		doubles;
	char	*temp;

	i = -1;
	j = -1;
	simples = 1;
	doubles = 1;
	temp = malloc(ft_strlen(str) + 1);
	if (!temp)
		return (-1); //Quizá convendría tener una funcion que gestione los errores
	while (str[++i])
	{
		if (str[i] == 34 && simples != -1)
			doubles *= -1;
		else if (str[i] == 39 && doubles != -1)
			simples *= -1;
		else
			temp[++j] = str[i];
	}
	return (temp);
}