#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}
