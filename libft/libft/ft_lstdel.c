/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:47:16 by klaurine          #+#    #+#             */
/*   Updated: 2019/08/29 19:37:25 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *p;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		p = (*alst)->next;
		free(*alst);
		*alst = p;
	}
}
