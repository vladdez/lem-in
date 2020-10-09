/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_belmon_ford_queue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:08:54 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:04:47 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_queue_bf	*init_belmon_ford(void)
{
	t_queue_bf *belmon_ford;

	if (!(belmon_ford = malloc(sizeof(t_queue_bf) * 1)))
		terminate(ERR_ALLOCATION);
	belmon_ford->type_room = IN_OUT;
	belmon_ford->room_name = NULL;
	belmon_ford->accumulated_value = 0;
	belmon_ford->parrent = NULL;
	belmon_ford->next = NULL;
	return (belmon_ford);
}

/*
** if (check_conditions_for_belmon_ford_queue -  1 - проходит, 0 - нет
*/

void		add_links_to_belmon_ford_queue(t_room *tmp_room,
t_queue_bf *belmon_ford, char *start_name)
{
	t_node		*tmp_link;
	t_queue_bf	*tmp_queue;
	t_queue_bf	*end_queue;
	int			i;

	i = 0;
	if (tmp_room != NULL && tmp_room->link != NULL &&
	tmp_room->link->node != NULL)
	{
		tmp_link = tmp_room->link;
		end_queue = find_end_of_queue(belmon_ford);
		while (tmp_link)
		{
			if (check_conditions_for_belmon_ford_queue(tmp_link,
			belmon_ford, tmp_room, start_name))
			{
				tmp_queue = init_belmon_ford();
				put_data_in_queue(tmp_queue, belmon_ford, tmp_link);
				end_queue->next = tmp_queue;
				end_queue = end_queue->next;
				i++;
			}
			tmp_link = tmp_link->next;
		}
		if (i == 0)
		{
			tmp_link = tmp_room->link;
			while (tmp_link)
			{
				if (ft_strcmp(tmp_link->node, tmp_room->room_name) == 0)
				{
					tmp_queue = init_belmon_ford();
					put_data_in_queue(tmp_queue, belmon_ford, tmp_link);
					end_queue->next = tmp_queue;
					break ;
				}
				tmp_link = tmp_link->next;
			}
		}
	}
}

t_queue_bf	*algorithm_belmon_ford(t_lem_in *lem_in)
{
	t_queue_bf	*belmon_ford;
	t_room		*tmp;

	belmon_ford = init_belmon_ford();
	put_start_data(belmon_ford, lem_in->start);
	while (belmon_ford != NULL && ft_strcmp(belmon_ford->room_name,
	lem_in->end->room_name) != 0)
	{
		tmp = find_room_with_type_in_hashtable(belmon_ford->room_name,
		belmon_ford->type_room, lem_in->ht_rooms);
		add_links_to_belmon_ford_queue(tmp, belmon_ford,
		lem_in->start->room_name);
		belmon_ford = belmon_ford->next;
	}
	return (belmon_ford);
}

/*
** 	//нужно продумать какой путь выбирать  что делать дальше если
** у нас есть еще end  как в примере в тетради
*/
