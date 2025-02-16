/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:17:58 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 07:38:43 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_player(t_player *player, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N')
				player->initial_direction = NORTH;
			else if (map[i][j] == 'W')
				player->initial_direction = WEST;
			else if (map[i][j] == 'S')
				player->initial_direction = SOUTH;
			else if (map[i][j] == 'E')
				player->initial_direction = EAST;
			if (ft_strchr("NWSE", map[i][j]))
			{
				player->position.y = i + 0.5;
				player->position.x = j + 0.5; 
				return ;
			}
		}
	}
}

int	validate_props(char **props, char *types, int line)
{
	int			i;
	char		identifier;
	const int	size = ft_strlen(types);

	if (str_arr_size(props) != size + 1)
		return (parser_panic(line, props[0], ERR_WRONG_FORMAT), false);
	i = 0;
	while (++i < size + 1)
	{
		identifier = types[i - 1];
		if (identifier == 'X' && !validate_extension(props[i], ".xpm"))
			return (parser_panic(line, props[i], ERR_ARG_XPM), false);
		if (identifier == 'R' && !is_rgb(props[i]))
			return (parser_panic(line, props[i], ERR_ARG_RGB), false);
		if (identifier == 'R' && !validate_rgb(strtorgb(props[i])))
			return (parser_panic(line, props[i], ERR_RGB_RANGE), false);
	}
	return (1);
}

int	parse_texture(t_scene *scene, char **props, int type, int line)
{
	t_texture *const	texture = &scene->options.textures[type - 2];

	if (!validate_props(props, "X", line))
		return (false);
	if (texture->path)
		return (parser_panic(line, "Multiple Texture", ERR_MULTIPLE_TEXTURE), \
		false);
	texture->path = ft_strdup(props[1]);
	if (!texture->path)
		return (panic("String Duplication", NULL, false));
	return (true);
}

int	parse_color(t_scene *scene, char **props, int type, int line)
{
	t_rgb **const	color = &scene->options.colors[type - 6];

	if (!validate_props(props, "R", line))
		return (false);
	if (*color)
		return (parser_panic(line, "Multiple Color", ERR_MULTIPLE_COLOR), \
		false);
	*color = ft_calloc(1, sizeof(t_rgb));
	if (!*color)
		return (panic("Malloc Error", NULL, false));
	**color = strtorgb(props[1]);
	return (true);
}

void 	print_map(char **map)
{
	int		i;

	i = -1;
	while (map[++i])
		printf("%s\n", map[i]);
}
char **ft_strarrdup(char **arr)
{
    char **result;
    int i = 0;
    int len = 0;

    if (!arr)
        return (NULL);
    while (arr[len])
        len++;
    result = (char **)malloc((len + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    while (i < len)
    {
        result[i] = ft_strdup(arr[i]);
        if (!result[i])
        {
            while (--i >= 0)
                free(result[i]);
            free(result);
            return (NULL);
        }
        i++;
    }
    result[len] = NULL;
    return (result);
}

void flood_fill(char **map, int y, int x, t_map *map_struct)
{
	if (y < 0 || x < 0 || y >= map_struct->height || x >= (int)ft_strlen(map[y]))
		return ;
	if (map[y][x] == '2' || map[y][x] == ' ')
		return ;
	map[y][x] = '2';
	flood_fill(map, y + 1, x, map_struct);
	flood_fill(map, y - 1, x, map_struct);
	flood_fill(map, y, x + 1, map_struct);
	flood_fill(map, y, x - 1, map_struct);
}

int check_flood(char **map, t_map *map_struct)
{
	int i;
	int j;

	i = -1;
	while (++i < map_struct->height)
	{
		j = -1;
		while (++j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == '0' || map[i][j] == '1')
				return(1);
		}
	}
	return (0);
}

int	parse_map(t_scene *scene, int fd, char *line, int *line_count)
{
	t_map *const	map = &scene->map;
	char **const	map_layout = load_map(fd, line, line_count);
	char **const 	map_copy = ft_strarrdup(map_layout);

	if (!map_layout)
		return (panic("Reading Map", NULL, 0));
	map->height = str_arr_size(map_layout);
	map->width = get_map_width(map_layout);
	set_player(&scene->player, map_layout);
	flood_fill(map_copy, (int)scene->player.position.y, \
		(int)scene->player.position.x, map);
	if (check_flood(map_copy, map))
		return (panic("Map", ERR_DOUBLE_MAP, 0));
	extend_map(map_layout, map->width);
	map->layout = map_layout;
	line = get_next_line(fd);
	if (line)
		return (free(line), parser_panic(++(*line_count), "Map File", \
		ERR_MAP_NOTLAST), false);
	if (!validate_map(map_layout))
		return (false);
	return (true);
}
