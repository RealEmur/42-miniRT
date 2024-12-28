#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = temp->next;
		if (temp->content)
			del(temp->content);
		free(temp);
	}
}
