/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:52:22 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 13:01:39 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int panic(char *tag, char *error, int rtrn_val)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    if (error)
	{
		ft_putstr_fd(tag, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd(error, STDERR_FILENO);
	}
	else
		perror(tag);
    return (rtrn_val);
}

void	parser_panic(int type, int line, char *title, char *err)
{
	int		fd;

	if (type == ERROR)
	{
		fd = STDERR_FILENO;
		ft_putendl_fd("Error", fd);
	}
	else if (type == WARNING)
	{
		fd = STDOUT_FILENO;
		ft_putstr_fd("Warning: ", fd);
	}
	ft_putstr_fd("Line ", fd);
	ft_putnbr_fd(line, fd);
	ft_putstr_fd(": ", fd);
	if (title)
	{
		ft_putstr_fd(title, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putendl_fd(err, fd);
}
