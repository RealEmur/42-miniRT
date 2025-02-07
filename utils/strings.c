/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:30:28 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 03:25:57 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	str_append(char **s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;
	
	if (!*s1)
	{
		*s1 = ft_strdup(s2);
		return (*s1 && true);
	}
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	str = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return false;
	ft_strlcpy(str, *s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, s2_len + 1);
	free(*s1);
	*s1 = str;
	return (true);
}

int	str_arr_size(char **strs)
{
	int		len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}

void free_str_arr(char **strs)
{
	int		i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}