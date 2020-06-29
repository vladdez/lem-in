/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:17:02 by klaurine          #+#    #+#             */
/*   Updated: 2019/08/31 17:38:48 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list;
	t_list *buffer;

	if (!lst || !f)
		return (NULL);
	if (!(list = f(lst)))
		return (NULL);
	buffer = list;
	while (lst->next)
	{
		lst = lst->next;
		if (!(buffer->next = f(lst)))
		{
			while (list)
			{
				buffer = list->next;
				free(list);
				list = buffer;
			}
			return (NULL);
		}
		buffer = buffer->next;
	}
	return (list);
}
