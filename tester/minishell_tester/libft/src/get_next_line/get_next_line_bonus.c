/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:14:34 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/21 08:13:37 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*return_remaining_line(int fd, char **buffer_res)
{
	char	*temp;

	if (buffer_res[fd] && *buffer_res[fd])
	{
		temp = check_reminder(&buffer_res[fd]);
		if (temp)
			return (temp);
	}
	if (buffer_res[fd] && *buffer_res[fd])
	{
		temp = ft_strdup(buffer_res[fd]);
		free(buffer_res[fd]);
		buffer_res[fd] = NULL;
		return (temp);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*buffer_res[FD_SETSIZE];
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	char			*temp;

	if (fd < 0 || fd >= FD_SETSIZE)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (handle_error_gnl(&buffer_res[fd]));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		buffer_res[fd] = manage_buffer(&buffer_res[fd], buffer);
		temp = check_reminder(&buffer_res[fd]);
		if (temp)
			return (temp);
	}
	return (return_remaining_line(fd, buffer_res));
}
/*
int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("test/gnl1.txt", O_RDONLY);
	fd2 = open("test/gnl2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}
	printf("------ Reading from gnl1.txt ------\n");
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("------ Reading from gnl2.txt ------\n");
	while ((line = get_next_line(fd2)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	return (0);
}*/
