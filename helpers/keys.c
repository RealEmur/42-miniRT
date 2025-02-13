/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:22:14 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/13 23:36:35 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	destroy_key_node(t_list	*node)
{
	ft_lstdelone(node, free);
}

t_list	*get_key_node(t_list *pressed_keys, int keycode)
{
	t_list	*key;
	int		*ptr_keycode;
	
	while (pressed_keys)
	{
		key = pressed_keys;
		ptr_keycode = key->content;
		if (keycode == *ptr_keycode)
			return (key);
		pressed_keys = pressed_keys->next;
	}
	return (NULL);
}

int	on_key_press(int keycode, void *param)
{
	t_list	**const pressed_keys = param;
	t_list	*lst;
	int		*keycode_ptr;
	
	if (!get_key_node(*pressed_keys, keycode))
	{
		keycode_ptr = malloc(sizeof(int));
		if (!keycode_ptr)
			return (panic("Malloc Error", NULL, false));
		lst = ft_lstnew(keycode_ptr);
		if (!lst)
			return (free(keycode_ptr), panic("Malloc Error", NULL, false));
		ft_lstadd_back(pressed_keys, lst);
		*keycode_ptr = keycode; 
	}
	return (true);
}

int	on_key_release(int keycode, void *param)
{
	t_list	**const pressed_keys = param;
	t_list	*lst;
	t_list	*target;
	
	target = get_key_node(*pressed_keys, keycode);
	lst = *pressed_keys;
	if (!target)
		return (true);
	else if (*pressed_keys == target)
		*pressed_keys = (*pressed_keys)->next;
	else
	{
		while (lst && lst->next != target)
			lst = lst->next;
		if (lst)
			lst->next = target->next;
	}
	destroy_key_node(target);
	return (true);
}

int	is_key_pressed(t_list *pressed_keys, int keycode)
{
	return (get_key_node(pressed_keys, keycode) || 0);
}

