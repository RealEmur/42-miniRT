#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*chr_dst;
	char	*chr_src;
	size_t	i;

	if (!dst && !src)
		return (dst);
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		chr_dst = (char *) dst;
		chr_src = (char *) src;
		i = 1;
		while (i <= len)
		{
			chr_dst[len - i] = chr_src[len - i];
			i++;
		}
	}
	return (dst);
}
