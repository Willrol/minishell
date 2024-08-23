/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:13:25 by aditer            #+#    #+#             */
/*   Updated: 2024/05/22 14:41:05 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*resize_line(char *line, ssize_t *line_size, ssize_t line_position)
{
	char	*temp_line;

	*line_size = *line_size + BUFFER_SIZE;
	temp_line = malloc(*line_size);
	if (!temp_line)
		return (NULL);
	ft_memcpy(temp_line, line, line_position);
	free(line);
	return (temp_line);
}

char	*read_line(int fd, t_gnl_data *data, char *line, ssize_t *line_size)
{
	ssize_t	line_position;

	line_position = 0;
	while (1)
	{
		if (data->buffer_position >= data->nb_read)
		{
			data->nb_read = read(fd, data->buffer, BUFFER_SIZE);
			data->buffer_position = 0;
			if (line_position > 0 && data->nb_read == 0)
				return (line[line_position] = '\0', line);
			if (data->nb_read <= 0)
				return (free(line), NULL);
		}
		if (line_position >= *line_size - 1)
		{
			line = resize_line(line, line_size, line_position);
			if (!line)
				return (NULL);
		}
		line[line_position++] = data->buffer[data->buffer_position++];
		if (data->buffer[data->buffer_position - 1] == '\n')
			return (line[line_position] = '\0', line);
	}
}

char	*get_next_line(int fd)
{
	static t_gnl_data	data;
	char				*line;
	ssize_t				line_size;

	line_size = BUFFER_SIZE;
	line = malloc(line_size);
	if (!line)
		return (NULL);
	line = read_line(fd, &data, line, &line_size);
	return (line);
}
