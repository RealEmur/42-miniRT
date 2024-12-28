#include "libft.h"

static void	clear_matrix(char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	free(strs);
}

static int	get_word_count(char *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*get_next_word(char	**s, char c)
{
	size_t	len;

	while (**s && **s == c)
		*s = *s + 1;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	if (len == 0)
		return (0);
	*s += len;
	return (ft_substr((const char *) *s - len, 0, len));
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*str;
	int		strs_size;
	int		i;

	str = (char *) s;
	strs_size = get_word_count((char *) s, c) + 1;
	strs = (char **) malloc(sizeof(char *) * strs_size);
	if (!strs)
		return (0);
	i = 0;
	while (i < strs_size)
	{
		strs[i] = get_next_word(&str, c);
		if (!strs[i] && i != strs_size - 1)
		{
			clear_matrix(strs, i);
			return (0);
		}
		i++;
	}
	return (strs);
}
