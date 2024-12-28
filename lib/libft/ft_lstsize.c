#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		c;

	c = 0;
	while (lst)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}
