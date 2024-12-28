#include "libft.h"

static int	get_num_length(int n)
{
	int		len;
	long	c;

	len = 0;
	c = (long) n;
	if (c < 0)
	{
		len++;
		c *= -1;
	}
	while (c >= 0)
	{
		c /= 10;
		len++;
		if (c == 0)
			break ;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	num;

	i = get_num_length(n);
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i] = '\0';
	i--;
	num = n;
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num >= 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
		if (num == 0)
			break ;
	}
	return (str);
}
