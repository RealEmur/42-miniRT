#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		divider;
	long	num;

	num = n;
	divider = 1;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	while (num / divider >= 10)
		divider *= 10;
	while (divider >= 1)
	{
		ft_putchar_fd('0' + (num / divider), fd);
		num = num % divider;
		divider /= 10;
	}
}
