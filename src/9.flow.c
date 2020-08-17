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

#include "lem-in.h"

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

void	run_new_ant(t_path *pa, t_lem_in *lem_in, int i, int f)
{
	t_path	*curr;

	push_ants_along(pa, lem_in, i);
	curr = pa;
	print_paths_with_ants(curr, f);
}

int		lever(int lev, t_lem_in *lem_in)
{
	int		cut;
	int		i;
	int		empty;

	empty = 0;
	i = 0;
	cut = 0;
	if (lem_in->path_num == 1)
		return (0);
	else
	{
		while (cut < lev && i <= lem_in->path_num)
		{
			if (lem_in->paths[i])
				cut += lem_in->paths[i]->len;
			else
				empty++;
			i++;
		}
		i--;
		i -= empty;
		return (i);
	}
}

void	count_new_ants(t_lem_in *lem_in, int f, int flows_used_this_run, int ant_index)
{
	t_path	*path_tmp; // конкретный выбранный поток

	while (f <= flows_used_this_run)
	{
		path_tmp = lem_in->paths[f];
		if (path_tmp)
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
		else
			flows_used_this_run++;
		f++;
	}
}

void	flow(t_lem_in *lem_in, int ant_index, int flows_used_this_run) // AntIndex номер муравья, FlowsUsedThisRun количество потоков в этот толчок
{
	int		unused_ants;
	int		f; // от 1 идет до FlowsUsedThisRun, чтобы начинал с короткого пути
	int		maxf; // сколько потоков было использовано сначала и которые нужно опустошить от муравьев
	int		lines;
	int		supermax;

	lines = 0;
	unused_ants = lem_in->ant_num;
	point_heads(lem_in);
	maxf = -2;
	supermax = -2;
	while (lem_in->ants_start <= lem_in->ant_num &&
			lem_in->ant_num != lem_in->ants_end)
	{
		if (flows_used_this_run > 1)
			flows_used_this_run = lever(unused_ants, lem_in);
		unused_ants -= flows_used_this_run;
		maxf = (maxf == -2) ? flows_used_this_run : maxf;
		supermax = (supermax == -2) ? flows_used_this_run : supermax;
		f = 0;
		ant_index = index_manager(lem_in, supermax, ant_index);
		count_new_ants(lem_in, f, flows_used_this_run, ant_index);
		if (flows_used_this_run != maxf)
			maxf = push_old_ants(lem_in, supermax, flows_used_this_run, ant_index);
		ft_printf("\n");
		lines++;
	}
	ft_printf("\nLines printed: %d\n", lines);
}
