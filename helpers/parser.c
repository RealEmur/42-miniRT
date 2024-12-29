/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:59:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/29 02:30:07 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	parser_panic(int line, char *title, char *err)
{
	ft_putstr_fd("Error\nLine ", STDIN_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(title, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
}

t_object	*parse_object(char **props, int line)
{
	char	*const	identifier = props[0];
	
	if (!ft_strncmp(identifier, "A", 2))
		return (parse_ambient(props, line));
	else if (!ft_strncmp(identifier, "C", 2))
		return (parse_camera(props, line));
	else if (!ft_strncmp(identifier, "L", 2))
		return (parse_light(props, line));
	else if (!ft_strncmp(identifier, "sp", 3))
		return (parse_sphere(props, line));
	else if (!ft_strncmp(identifier, "pl", 3))
		return (parse_plane(props, line));
	else if (!ft_strncmp(identifier, "cy", 3))
		return (parse_cylinder(props, line));
	return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
}

int	parse_line(char *line, t_list **objects, int line_count)
{
	//A 0.2 255,255,255
	char		*const	trimmed = ft_strtrim(line, "\n");
	char		**splitted;
	t_list		*lst;
	t_object	*object;

	if (!trimmed)
		return (false);
	splitted = ft_split(trimmed, ' ');
	free(trimmed);
	if (str_arr_size(splitted) == 0)
		return (true);	
	object = parse_object(splitted, line_count);
	if (!object)
		return (free_str_arr(splitted), false);
	lst = ft_lstnew(object);
	if (!lst)
		return (free_str_arr(splitted), false);
	ft_lstadd_back(objects, lst);
	free_str_arr(splitted);
	return (true);
}

int	parse_lines_from_file(int fd, t_list **objects)
{
	int			line_count;
	char		*line;

	line_count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!parse_line(line, objects, line_count))
			return (free(line), false);
		line_count++;
		free(line);
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
	if (!parse_lines_from_file(fd, &objects))
		return (ft_lstclear(&objects, free), NULL);
    return (objects);   
}