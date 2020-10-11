/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_me_free_lem2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 21:52:33 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:03:36 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	free_found_path(t_path *path)
{
	t_path *tmp;

	while (path)
	{
		tmp = path->next;
		free(path->name);
		free(path);
		path = tmp;
	}
}

void	free_paths(t_path **pa, int path_num)
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
	if (pa != NULL)
		free(pa);
}

void	free_node(t_node **sentenced)
{
	t_node *kill;

	if (sentenced)
		while ((*sentenced))
		{
			kill = (*sentenced);
			(*sentenced) = (*sentenced)->next;
			free(kill->node);
			kill->node = NULL;
			free(kill);
			kill = NULL;
		}
}
