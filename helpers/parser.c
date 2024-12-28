/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:59:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 18:56:12 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"



t_object	*parse_object(char **props)
{
	char	*const	identifier = props[0];
	
	if (!ft_strncmp(identifier, "A", 2))
		return (parse_ambient_lightning(props));
	else if (!ft_strncmp(identifier, "C", 2))
		return (parse_camera(props));
	/*
	else if (!ft_strncmp(identifier, "L", 2))
		return (LIGHT);
	else if (!ft_strncmp(identifier, "sp", 3))
		return (SPHERE);
	else if (!ft_strncmp(identifier, "pl", 3))
		return (PLANE);
	else if (!ft_strncmp(identifier, "cy", 3))
		return (CYLINDER); */
	return (NULL);	
}

int	read_lines_from_scene(int fd, t_list **objects)
{
	t_object	*obj;
	t_list		*lst;
	char		*line;
	char		*trimmed;
	char		**splitted;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		trimmed = ft_strtrim(line, "\n");
		free(line);
		if (!trimmed)
			return (free_str_arr(splitted), false);
		splitted = ft_split(trimmed, ' ');
		if (str_arr_size(splitted))
		{
			obj = parse_object(splitted);
			if (!obj)
				return (free_str_arr(splitted), false);
			lst = ft_lstnew(obj);
			if (!lst)
				return (free_str_arr(splitted), false);
			ft_lstadd_back(objects, lst);
		}
		free_str_arr(splitted);
	}
	return (true);
}

t_list	*parser(char *path)
{
	t_list	*objects;
	
	objects = NULL;
	if (!is_valid_extension(path))
		return (panic(path, ERR_EXTENSION, -1), NULL);
    const int	fd = open(path, O_RDONLY);
    if (fd == -1)
		return (panic(path, NULL, -1), NULL);
	if (!read_lines_from_scene(fd, &objects))
		return (ft_lstclear(&objects, free), NULL);
    return (objects);   
}