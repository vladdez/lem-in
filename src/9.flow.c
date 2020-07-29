/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.flow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 18:11:00 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/27 18:11:04 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_paths_with_ants(t_path *curr)
{
	if (curr == NULL)
		return;
	print_paths_with_ants(curr->next);
	if (curr->head != 1 && curr->ant_index != 0)
		ft_printf("L%d-%s ", curr->ant_index, curr->name);
}

void		push_ants_along(t_path *pa, t_lem_in *lem_in, int i)
{
	t_path *curr;
	int tmp;
	int tmp2;

	curr = pa;
	tmp = 0;
	tmp2 = 0;
	while (i)
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


void	flow(t_lem_in *lem_in)
{
	int		i;
	t_path 	*pa;
	t_path 	*curr;

	pa = lem_in->paths[1];
	lem_in->ants_start = 0;
	pa->head = 1;
	i = 1;
	while (lem_in->ants_start <= lem_in->ant_num && lem_in->ant_num != lem_in->ants_end)
	{
		if (lem_in->ants_start < lem_in->ant_num)
		{
			lem_in->ants_start++;
			pa->ant_index = lem_in->ants_start;
		}
		else
			pa->ant_index = 0;
		if (i != pa->len + 1)
			i++;
		push_ants_along(pa, lem_in, i);
		curr = pa;
		print_paths_with_ants(curr);
		ft_printf("\n");
	}

		


}
