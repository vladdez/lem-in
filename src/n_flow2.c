/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.flow2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:31:18 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/17 11:31:21 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_paths_with_ants(t_path *curr, int i)
{
	if (curr == NULL)
		return ;
	print_paths_with_ants(curr->next, i);
	if (curr->head != 1 && curr->ant_index != 0)
	{
		if (i == 0)
			ft_printf("{blue}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 1)
			ft_printf("{cyan}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 2)
			ft_printf("{green}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 3)
			ft_printf("{yellow}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 4)
			ft_printf("{magenta}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i > 4)
			ft_printf("{red}L%d-%s{eoc} ", curr->ant_index, curr->name);
	}
}

void	push_ants_along(t_path *pa, t_lem_in *lem_in, int until)
{
	t_path	*curr;
	int		changer;
	int		keeper;

	curr = pa;
	changer = 0;
	keeper = 0;
	while (curr && until)
	{
		if (curr->head == 1)
			changer = pa->ant_index;
		else
		{
			keeper = curr->ant_index;
			curr->ant_index = changer;
			changer = keeper;
			if (curr->next == NULL)
			{
				if (curr->ant_index != 0)
					lem_in->ants_end++;
			}
		}
		curr = curr->next;
		until--;
	}
}

int		index_manager(t_lem_in *lem_in, int maxf, int ant_index)
{
	if (!lem_in->paths[maxf])
		maxf--;
	if (ant_index != lem_in->paths[maxf]->len + 1)
		ant_index++;
	return (ant_index);
}

int		check_emptyness_of_path(t_path *tmp_pa)
{
	int		i;
	t_path	*curr;

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

int		push_old_ants(t_lem_in *lem_in, int supermax,
int flows_used_this_run, int ant_index)
{
	t_path	*curr;
	t_path	*pa;
	int		tmp;

	tmp = lem_in->ants_end;
	if (flows_used_this_run < 0)
		flows_used_this_run = 0;
	else
		flows_used_this_run++;
	while (flows_used_this_run <= supermax)
	{
		pa = lem_in->paths[flows_used_this_run];
		pa->ant_index = 0;
		push_ants_along(pa, lem_in, ant_index);
		curr = lem_in->paths[flows_used_this_run];
		print_paths_with_ants(curr, flows_used_this_run);
		flows_used_this_run++;
	}
	flows_used_this_run--;
	return (flows_used_this_run);
}
