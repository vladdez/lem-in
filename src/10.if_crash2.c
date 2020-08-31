/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.suurb_flow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 16:03:29 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/18 16:03:43 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"


int		is_enough(t_lem_in *lem_in)
{
	int		p;
	int		totallen;
	int		path_num_fl;

	path_num_fl = lem_in->path_num - 1;
	p = 0;
	totallen = 0;
	while (p != path_num_fl)
	{
		if (lem_in->paths[p])
			totallen += lem_in->paths[p]->len;
		p++;
	}
	if (lem_in->ant_num > totallen)
		return (0);
	else
		return (1);
	return (0);
}

void	get_mem(t_lem_in *lem_in, int i)
{
	t_path	*pa;
	t_room	*r;


	r = NULL;
	pa = lem_in->paths[0];
	pa = pa->next;
	r = find_room_in_hashtable(pa->name, lem_in->ht_rooms);
	r->cut = CUTTED;
	if (i == 1)
		lem_in->mem = r;
	else if (i == 2)
	{
		lem_in->mem->cut = UNCUT;
	}
}

