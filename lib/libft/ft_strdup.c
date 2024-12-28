#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + 1;
	str = (char *) malloc(sizeof(char) * len);
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len);
	return (str);
}
