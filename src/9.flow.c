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
	int     j;

	j = 0;
	i = lem_in->path_num;
	while (j != i)
	{
	    if (lem_in->paths[j])
		    lem_in->paths[j]->head = 1;
		j++;
	}
}

void	run_new_ant(t_path *pa, t_lem_in *lem_in, int i)
{
	t_path	*curr;

	push_ants_along(pa, lem_in, i);
	curr = pa;
	print_paths_with_ants(curr);
}

int     check_emptyness_of_path(t_path	*tmp_pa)
{
    int     i;
    t_path  *curr;

    i = 0;
    curr = tmp_pa;
    while (curr && curr->ant_index == 0)
    {
        i++;
        curr = curr->next;
    }
    if (i == tmp_pa->len)
        return (1);
    else
        return (0);
}

int		push_old_ants(t_lem_in *lem_in, int supermax, int FlowsUsedThisRun, int AntIndex)
{
	t_path	*curr;
	t_path	*tmp_pa;
	int     EmptyPath;

    EmptyPath = 0;
	while (FlowsUsedThisRun <= supermax)
	{
        tmp_pa = lem_in->paths[FlowsUsedThisRun];
		if (tmp_pa)
        {
            tmp_pa->ant_index = 0;
            push_ants_along(tmp_pa, lem_in, AntIndex);
            curr = lem_in->paths[FlowsUsedThisRun];
            print_paths_with_ants(curr);
            EmptyPath += check_emptyness_of_path(tmp_pa);
        }
		else
		    supermax++;
        FlowsUsedThisRun++;
	}
    supermax -= EmptyPath;
	return (supermax);
}

int		lever(int lev, t_lem_in *lem_in)
{
	int		cut;
	int		i;
	int     empty;

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

void	count_new_ants(t_lem_in *lem_in, int f, int FlowsUsedThisRun, int AntIndex)
{
	t_path	*path_tmp; // конкретный выбранный поток

	while (f <= FlowsUsedThisRun)
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
            run_new_ant(path_tmp, lem_in, AntIndex);
        }
        else
            FlowsUsedThisRun++;
		f++;
	}
}

//maps/valid/vs/multiple_ways/1.map
int     IndexManager(t_lem_in *lem_in, int maxf, int AntIndex)
{
    if (!lem_in->paths[maxf])
        maxf--;
    if (AntIndex != lem_in->paths[maxf]->len + 1)
        AntIndex++;
    return (AntIndex);
}

void	flow(t_lem_in *lem_in, int AntIndex, int FlowsUsedThisRun) // AntIndex номер муравья, FlowsUsedThisRun количество потоков в этот толчок
{
	int		UnusedAnts;
	int		f; // от 1 идет до FlowsUsedThisRun, чтобы начинал с короткого пути
	int		maxf; // сколько потоков было использовано сначала и которые нужно опустошить от муравьев
	int		lines;
	int     supermax;

	lines = 0;
    UnusedAnts = lem_in->ant_num;
	point_heads(lem_in);
    maxf = -2;
    supermax = -2;
	while (lem_in->ants_start <= lem_in->ant_num &&
	lem_in->ant_num != lem_in->ants_end)
	{
		if (FlowsUsedThisRun > 1)
            FlowsUsedThisRun = lever(UnusedAnts, lem_in);
        UnusedAnts -= FlowsUsedThisRun;
		maxf = (maxf == -2) ? FlowsUsedThisRun : maxf;
        supermax = (supermax == -2) ? FlowsUsedThisRun : supermax;
		f = 0;
		AntIndex = IndexManager(lem_in, supermax, AntIndex);
		count_new_ants(lem_in, f, FlowsUsedThisRun, AntIndex);
		if (FlowsUsedThisRun != maxf)
            maxf = push_old_ants(lem_in, supermax, FlowsUsedThisRun, AntIndex);
		ft_printf("\n");
		lines++;
	}
	ft_printf("\nLines printed: %d\n", lines);
}
