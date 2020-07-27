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

void	flow(t_lem_in *lem_in)
{
	int i;
	t_path *pa;

	i = 1;
	pa = lem_in->paths[1];
	if (lem_in->path_num > 1)
	{
		
	}
	else
	{
		while (i <= lem_in->ant_num)
		{
			pa = pa->next;
			ft_printf("L%d-%s ", i, pa->name);
			i++;
			
		}

		

	}

}
