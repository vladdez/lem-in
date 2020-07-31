/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.flow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 18:11:00 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/31 13:56:31 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_paths_with_ants(t_path *curr)
{
	if (curr == NULL)
		return ;
	print_paths_with_ants(curr->next);
	if (curr->head != 1 && curr->ant_index != 0)
		ft_printf("L%d-%s ", curr->ant_index, curr->name);
}

void	push_ants_along(t_path *pa, t_lem_in *lem_in, int i)
{
	t_path	*curr;
	int		tmp;
	int		tmp2;

	curr = pa;
	tmp = 0;
	tmp2 = 0;
	while (curr && i)
	{
		if (curr->head == 1)
			tmp = pa->ant_index;
		else
		{
			tmp2 = curr->ant_index;
			curr->ant_index = tmp;
			tmp = tmp2;
			if (curr->next == NULL)
			{
				if (curr->ant_index != 0)
					lem_in->ants_end++;
			}
		}
		curr = curr->next;
		i--;
	}
}

void	point_heads(t_lem_in *lem_in)
{
	int		i;

	i = lem_in->path_num;
	while (i != 0)
	{
		lem_in->paths[i]->head = 1;
		i--;
	}
}

void	run_new_ant(t_path *pa, t_lem_in *lem_in, int i)
{
	t_path	*curr;

	push_ants_along(pa, lem_in, i);
	curr = pa;
	print_paths_with_ants(curr);
}

int		push_old_ants(t_lem_in *lem_in, int maxk, int j, int i)
{
	t_path	*curr;
	t_path	*pa;
	int		tmp;

	j++;
	tmp = lem_in->ants_end;
	while (j <= maxk)
	{
		pa = lem_in->paths[j];
		pa->ant_index = 0;
		push_ants_along(pa, lem_in, i);
		curr = lem_in->paths[j];
		print_paths_with_ants(curr);
		j++;
	}
	if (tmp != lem_in->ants_end)
		maxk -= (tmp - lem_in->ants_end);
	return (maxk);
}

int		lever(int lev, t_lem_in *lem_in)
{
	int		cut;
	int		i;

	i = 1;
	cut = 0;
	if (lem_in->path_num == 1)
		return (1);
	else
	{
		while (cut < lev && i <= lem_in->path_num)
		{
			cut += lem_in->paths[i]->len;
			i++;
		}
		i--;
		return (i);
	}
}

void	count_new_ants(t_lem_in *lem_in, int k, int j, int i)
{
	t_path	*pa; // конкретный выбранный поток

	while (k <= j)
	{
		pa = lem_in->paths[k];
		if (lem_in->ants_start < lem_in->ant_num)
		{
			lem_in->ants_start++;
			pa->ant_index = lem_in->ants_start;
		}
		else
			pa->ant_index = 0;
		run_new_ant(pa, lem_in, i);
		k++;
	}
}

void	flow(t_lem_in *lem_in, int i, int j) // i сколько узлов нужно протолкнуть, j количество потоков в этот толчок
{
	int		lev;
	int		k; // от 1 идет до j, чтобы начинал с короткого пути
	int		maxk; // сколько потоков было использовано сначала и которые нужно опустошить от муравьев

	lev = lem_in->ant_num;
	point_heads(lem_in);
	maxk = -2;
	while (lem_in->ants_start <= lem_in->ant_num &&
	lem_in->ant_num != lem_in->ants_end)
	{
		if (j > 1)
			j = lever(lev, lem_in);
		lev = lev - j;
		if (maxk == -2)
			maxk = j;
		k = 1;
		if (i != lem_in->paths[maxk]->len + 1)
			i++;
		count_new_ants(lem_in, k, j, i);
		if (j != maxk)
			maxk = push_old_ants(lem_in, maxk, j, i);
		ft_printf("\n");
	}
}
