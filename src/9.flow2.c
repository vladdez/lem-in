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
			ft_printf("{red}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 1)
			ft_printf("{green}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 2)
			ft_printf("{yellow}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 3)
			ft_printf("{blue}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 4)
			ft_printf("{magenta}L%d-%s{eoc} ", curr->ant_index, curr->name);
		else if (i == 4)
			ft_printf("{cian}L%d-%s{eoc} ", curr->ant_index, curr->name);
	}
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

int		push_old_ants(t_lem_in *lem_in, int supermax, int flows, int ant_index)
{
	t_path	*curr;
	t_path	*tmp_pa;
	int		empty_path;

	empty_path = 0;
	while (flows <= supermax)
	{
		tmp_pa = lem_in->paths[flows];
		if (tmp_pa)
		{
			tmp_pa->ant_index = 0;
			push_ants_along(tmp_pa, lem_in, ant_index);
			curr = lem_in->paths[flows];
			print_paths_with_ants(curr, flows);
			empty_path += check_emptyness_of_path(tmp_pa);
		}
		else
			supermax++;
		flows++;
	}
	supermax -= empty_path;
	return (supermax);
}

int		index_manager(t_lem_in *lem_in, int maxf, int ant_index)
{
	if (!lem_in->paths[maxf])
		maxf--;
	if (ant_index != lem_in->paths[maxf]->len + 1)
		ant_index++;
	return (ant_index);
}
