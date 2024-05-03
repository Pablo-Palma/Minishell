/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:14:34 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/21 08:13:06 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*handle_error_gnl(char **buffer_res)
{
	free(*buffer_res);
	*buffer_res = NULL;
	return (NULL);
}

char	*check_reminder(char **buffer_res)
{
	char	*newline_pos;
	char	*line;
	char	*temp_res;

	newline_pos = ft_strchr(*buffer_res, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strjoin(*buffer_res, "\n");
		temp_res = *buffer_res;
		if (*(newline_pos + 1) != '\0')
			*buffer_res = ft_strdup(newline_pos + 1);
		else
			*buffer_res = NULL;
		free(temp_res);
		return (line);
	}
	return (NULL);
}

char	*manage_buffer(char **buffer_res, char *buffer)
{
	char	*temp;

	if (!*buffer_res)
		return (ft_strdup(buffer));
	temp = ft_strjoin(*buffer_res, buffer);
	free (*buffer_res);
	*buffer_res = NULL;
	return (temp);
}

char	*return_remaining_line(char **buffer_res)
{
	char	*temp;

	if (buffer_res && *buffer_res)
	{
		temp = check_reminder(buffer_res);
		if (temp)
			return (temp);
		temp = ft_strdup(*buffer_res);
		free(*buffer_res);
		*buffer_res = NULL;
		return (temp);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*buffer_res = NULL;
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	char			*temp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (handle_error_gnl(&buffer_res));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		buffer_res = manage_buffer(&buffer_res, buffer);
		temp = check_reminder(&buffer_res);
		if (temp)
			return (temp);
	}
	return (return_remaining_line(&buffer_res));
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test/gnl.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
