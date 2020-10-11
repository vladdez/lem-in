/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.flow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 18:11:00 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/17 11:28:53 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	point_heads(t_lem_in *lem_in)
{
	int		i;
	int		j;

	j = 0;
	i = lem_in->path_num;
	while (j != i)
	{
		if (lem_in->paths[j])
			lem_in->paths[j]->head = 1;
		j++;
	}
}

void	run_new_ant(t_path *pa, t_lem_in *lem_in, int ant_index, int f)
{
	t_path	*curr;

	push_ants_along(pa, lem_in, ant_index);
	curr = pa;
	print_paths_with_ants(curr, f);
}

void	count_new_ants(t_lem_in *lem_in, int f, int flows_used_this_run,
int ant_index)
{
	t_path	*path_tmp;

	while (f <= flows_used_this_run)
	{
		path_tmp = lem_in->paths[f];
		if (path_tmp && path_tmp->next)
		{
			if (lem_in->ants_start < lem_in->ant_num)
			{
				lem_in->ants_start++;
				path_tmp->ant_index = lem_in->ants_start;
			}
			else
				path_tmp->ant_index = 0;
			run_new_ant(path_tmp, lem_in, ant_index, f);
		}
		else if (f < lem_in->path_num)
			flows_used_this_run++;
		f++;
	}
}

int		lever(int ant_unused, t_lem_in *lem_in, int i)
{
	int		cut;
	int		res;
	int		dif;

	cut = 0;
	res = -1;
	if (lem_in->path_num == 0)
		return (0);
	else if (ant_unused < 0)
		return (-1);
	else
	{
		while (lem_in->paths[i])
		{
			dif = (lem_in->paths[i]->len * i) - cut;
			cut += lem_in->paths[i]->len;
			i++;
			ant_unused--;
			if (ant_unused >= dif)
				res++;
		}
		if (res == -1)
			res++;
		return (res);
	}
}

void	flow(t_lem_in *lem_in, int ant_index, int flows_used_this_run)
{
	int		supermax;
	int		ant_unused;

	ant_unused = lem_in->ant_num;
	point_heads(lem_in);
	supermax = lever(ant_unused, lem_in, 0);
	while (lem_in->ants_start <= lem_in->ant_num &&
			lem_in->ant_num != lem_in->ants_end)
	{
		flows_used_this_run = lever(ant_unused, lem_in, 0);
		ant_index = index_manager(lem_in, supermax, ant_index);
		ant_unused = ant_unused - 1 - flows_used_this_run;
		if (flows_used_this_run >= 0)
			count_new_ants(lem_in, 0, flows_used_this_run, ant_index);
		if (flows_used_this_run != supermax)
			supermax = push_old_ants(lem_in, supermax,
			flows_used_this_run, ant_index);
		ft_printf("\n");
		lem_in->lines++;
	}
}
