/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:03:25 by tkul              #+#    #+#             */
/*   Updated: 2025/02/17 18:03:26 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*chr_dst;
	char		*chr_src;

	if (!dst && !src)
		return (dst);
	chr_dst = (char *) dst;
	chr_src = (char *) src;
	i = 0;
	while (i < n)
	{
		chr_dst[i] = chr_src[i];
		i++;
	}
	return (dst);
}
