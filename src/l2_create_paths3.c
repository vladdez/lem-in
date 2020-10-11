/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l2_create_path3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:51:23 by kysgramo          #+#    #+#             */
/*   Updated: 2020/09/03 16:51:29 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		len_of_actual_paths(t_lem_in *lem_in)
{
	int		i;
	int		j;
	t_path	**p;

	i = 0;
	j = 0;
	p = lem_in->paths;
	while (p[i] != NULL)
	{
		if (p[i] && p[i]->next)
			j++;
		i++;
	}
	return (j);
}

void	check_order(t_path **paths, t_lem_in *lem_in, int i, int k)
{
	t_path	**curr;
	t_path	*tmp;
	int		j;

	curr = paths;
	tmp = NULL;
	j = len_of_actual_paths(lem_in);
	if (j > 1)
	{
		while (k < j)
		{
			i = 1;
			while (curr[i])
			{
				if (curr[i]->len < curr[i - 1]->len)
				{
					tmp = curr[i];
					curr[i] = curr[i - 1];
					curr[i - 1] = tmp;
				}
				i++;
			}
			k++;
		}
	}
}

void	upd_visits(t_lem_in *lem_in, t_room *tmp_room)
{
	tmp_room->bfs_visit = lem_in->bfs_used;
	tmp_room->ek_visit = lem_in->ek_used;
}
