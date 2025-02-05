/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/05 17:49:51 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int main(int size, char **args)
{
	t_scene	*const scene = &(t_scene){0};

    if (size == 2)
    {
		parser(args[1], scene);
	}	
    else 
        return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
    return (EXIT_SUCCESS);
}