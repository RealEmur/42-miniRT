/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 02:44:24 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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