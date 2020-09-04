/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.2.print_hashtable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 12:03:38 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/21 12:12:40 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_incominglinks(t_room *tmp2)
{
	t_node	*tmp;

	tmp = tmp2->incoming_links;
	while (tmp)
	{
		ft_printf("%s->", tmp->node);
		tmp = tmp->next;
	}
}

void	print_outgoinglinks(t_room *tmp2)
{
	t_node	*tmp;

	tmp = tmp2->outgoing_links;
	while (tmp)
	{
		ft_printf("->%s", tmp->node);
		tmp = tmp->next;
	}
}

void	print_links(t_room *tmp2)
{
	t_node	*tmp;

	tmp = tmp2->link;
	while (tmp)
	{
		ft_printf("->%s", tmp->node);
		tmp = tmp->next;
	}
}

void	print_ht_rooms_with_direction(t_hashtable *ht_rooms)
{
	int		i;
	t_room	*tmp2;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (ht_rooms->room[i] != NULL)
		{
			tmp2 = ht_rooms->room[i];
			while (tmp2)
			{
				if (tmp2->incoming_links->node != NULL &&
					tmp2->incoming_links != NULL)
					print_incominglinks(tmp2);
				ft_printf("%s[%d]", tmp2->room_name, tmp2->bfs_level);
				if (tmp2->outgoing_links->node != NULL)
					print_outgoinglinks(tmp2);
				ft_printf("    ");
				tmp2 = tmp2->next;
			}
			ft_printf("\n");
		}
		i++;
	}
	ft_putendl("End of the hashtable\n");
}

void	print_ht_rooms(t_hashtable *ht_rooms)
{
	int		i;
	t_room	*tmp2;

	i = 0;
	ft_printf("\n");
	while (i < TABLE_SIZE)
	{
		if (ht_rooms->room[i] != NULL)
		{
			tmp2 = ht_rooms->room[i];
			while (tmp2)
			{
				ft_printf(" %s[%d]", tmp2->room_name, tmp2->bfs_level);
				if (tmp2->link != NULL)
					print_links(tmp2);
				tmp2 = tmp2->next;
				ft_printf("    ");
			}
			ft_printf("\n");
		}
		i++;
	}
	ft_putendl("End of the hashtable\n");
}
