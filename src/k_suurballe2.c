/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_suurballe2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:46:52 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 21:46:55 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	clean_all_current_pathes(t_path **pa, int path_num)
{
	int		i;
	t_path	*kill;

	i = 0;
	while (i <= path_num)
	{
		if (pa[i] != NULL)
		{
			while (pa[i])
			{
				kill = pa[i];
				pa[i] = pa[i]->next;
				free(kill->name);
				free(kill);
			}
		}
		i++;
	}
}

void	edmon_karts_by_link_price(t_lem_in *lem_in)
{
	t_room	*tmp_room;
	t_path	*tmp_path;
	int		len;
	int		i;
	int		max;

	tmp_path = NULL;
	i = 0;
	max = find_posible_ways_number(lem_in->end->link);
	while (i < max)
	{
		tmp_room = lem_in->end;
		lem_in->paths[i] = create_one_path(lem_in->end);
		len = create_way_sub_with_price(lem_in, tmp_path, tmp_room, i);
		if (lem_in->paths[i])
		{
			lem_in->paths[i]->len = len;
			i++;
			lem_in->path_num++;
		}
		else if (len == -1)
			max--;
	}
}

void	clean_all_edmon_karts_marks_in_line(t_room *tmp)
{
	while (tmp)
	{
		tmp->ek_visit = UNVISITED;
		tmp = tmp->next;
	}
}

void	clean_all_edmon_karts_marks_in_all_ht(t_hashtable *ht)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (ht->room[i] != NULL)
			clean_all_edmon_karts_marks_in_line(ht->room[i]);
		i++;
	}
}
