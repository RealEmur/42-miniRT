/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:49:39 by tkul              #+#    #+#             */
/*   Updated: 2024/12/29 18:53:19 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void    init_mlx(t_scene *scene)
{
    scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, 1920, 1080, "Hello world!");
	mlx_loop(scene->mlx);
}