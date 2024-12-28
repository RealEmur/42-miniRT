#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_s;
	size_t			i;

	char_s = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (char_s[i] == (unsigned char) c)
			return (char_s + i);
		i++;
	}
	return (0);
}
