/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:52:22 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 05:39:18 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	panic(char *tag, char *error, int rtrn_val)
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

void	parser_panic(int line, char *title, char *err)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd("Line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (title)
	{
		ft_putstr_fd(title, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err, STDERR_FILENO);
}
