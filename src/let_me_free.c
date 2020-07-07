/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_me_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:02:52 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/07 18:31:30 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void    free_rooms(t_room **sentenced)
{
	t_room *kill;

	if (sentenced)
		while ((*sentenced))
		{
			kill = (*sentenced);
			(*sentenced) = (*sentenced)->next;
			free(kill);
		}
}

void    free_links(t_link **sentenced)
{
	t_link *kill;

	if (sentenced)
		while ((*sentenced))
		{
			kill = (*sentenced);
			(*sentenced) = (*sentenced)->next;
			free(kill);
		}
}

void    free_lem_in(t_lem_in **lem_in)
{
	if (lem_in && *lem_in)
	{
		free_rooms(&(*lem_in)->rooms);
		free_links(&(*lem_in)->links);
		free((*lem_in));
		(*lem_in) = NULL;
	}
}
