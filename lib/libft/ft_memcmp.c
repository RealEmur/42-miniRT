#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*chr_s1;
	unsigned char	*chr_s2;
	size_t			i;

	chr_s1 = (unsigned char *) s1;
	chr_s2 = (unsigned char *) s2;
	i = 0;
	while (i < n && chr_s1[i] == chr_s2[i])
		i++;
	if (i == n)
		return (0);
	return (chr_s1[i] - chr_s2[i]);
}
