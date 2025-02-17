/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:04:22 by tkul              #+#    #+#             */
/*   Updated: 2025/02/17 18:04:23 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	set_initial_fdata(char **data)
{
	*data = (char *) malloc(sizeof(char));
	if (*data)
		**data = '\0';
	return (*data != 0);
}

void	swap_str_and_free(char **str, char *newStr)
{
	free(*str);
	*str = newStr;
}

char	*free_fdata(char	**fdata)
{
	if (*fdata)
	{
		free(*fdata);
		*fdata = 0;
	}
	return (0);
}

char	*get_line(char *file_data)
{
	size_t	len;

	len = 0;
	while (file_data[len])
		if (file_data[len++] == '\n')
			break ;
	return (substr(file_data, 0, len));
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	static char	*file_data[1024] = {0};

	if (fd < 0 || (!file_data[fd] && !set_initial_fdata(&file_data[fd])))
		return (0);
	bytes_read = 0;
	while (file_data[fd] && !strchr(file_data[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1)
			break ;
		buffer[bytes_read] = '\0';
		swap_str_and_free(&file_data[fd], strjoin(file_data[fd], buffer));
	}
	if (!file_data[fd] || !*file_data[fd] || bytes_read == -1)
		return (free_fdata(&file_data[fd]));
	line = get_line(file_data[fd]);
	if (!line)
		return (free_fdata(&file_data[fd]));
	swap_str_and_free(&file_data[fd], \
	substr(file_data[fd], strlen(line), \
	strlen(file_data[fd]) - strlen(line)));
	return (line);
}
