/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.create_paths2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:58:16 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/17 18:58:44 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room	*find_best_room(t_room *cur, t_hashtable *ht_rooms)
{
	t_room *tmp;

	if ((len_nei(cur->incoming_links) == 1))
		return (find_room_in_hashtable(cur->incoming_links->node, ht_rooms));
	else
		tmp = find_lowest_bfs(cur->incoming_links, ht_rooms);
	return (tmp);
}

void	print_ants_for_short_circuit(t_lem_in *lem_in)
{
	int i;

	i = 1;
	while (i <= lem_in->ant_num)
	{
		ft_printf("{blue}L%i-%s{eoc} ", i, lem_in->end->room_name);
		i++;
	}
	ft_printf("\n");
}

int		is_short_circuit(t_lem_in *lem_in)
{
	t_node	*cur;
	int		p;

	p = 0;
	cur = lem_in->start->link;
	while (cur)
	{
		if (!ft_strcmp(cur->node, lem_in->end->room_name))
		{
			print_ants_for_short_circuit(lem_in);
			return (0);
		}
		else
			cur = cur->next;
		p++;
	}
	return (p);
}

int		len_nei(t_node *n)
{
	int		len;
	t_node	*curr;

	len = 0;
	curr = n;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}

void	delete_current_path(t_path *path)
{
	t_path *tmp;

	tmp = path;
	while (tmp)
	{
		tmp = path->next;
		free(path->name);
		free(path);
		path = tmp;
	}
}
