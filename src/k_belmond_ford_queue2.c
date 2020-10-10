/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_belmond_ford_queue2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:17:22 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 22:17:25 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		put_start_data(t_queue_bf *belmon_ford, t_room *start)
{
	if (!(belmon_ford->room_name = ft_strdup(start->room_name)))
		terminate(ERR_ALLOCATION);
}

void		put_data_in_queue(t_queue_bf *tmp_queue,
t_queue_bf *belmon_ford, t_node *link)
{
	if (!(tmp_queue->room_name = ft_strdup(link->node)))
		terminate(ERR_ROOM_INIT);
	tmp_queue->type_room = link->type_room;
	tmp_queue->parrent = belmon_ford;
	tmp_queue->accumulated_value = belmon_ford->accumulated_value + link->price;
}

t_queue_bf	*find_end_of_queue(t_queue_bf *belmon_ford)
{
	t_queue_bf *tmp;

	tmp = belmon_ford;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int			is_loop(char *node, t_queue_bf *belmman_ford)
{
	t_queue_bf	*tmp;
	int			i;

	tmp = belmman_ford;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(node, tmp->room_name) == 0)
			i++;
		tmp = tmp->parrent;
		if (i > 5)
			return (0);
	}
	return (1);
}

/*
** parrent
** dub room
** start room => cycle
*/

int			check_conditions_for_belmon_ford_queue(t_node *link,
t_queue_bf *belmman_ford, t_room *room, char *start_name)
{
	if (link->direction == UPSTREAM)
		return (0);
	if (belmman_ford->parrent != NULL && ft_strcmp(link->node,
	belmman_ford->parrent->room_name) == 0)
		return (0);
	if (ft_strcmp(link->node, room->room_name) == 0)
		return (0);
	if (ft_strcmp(link->node, start_name) == 0)
		return (0);
	if (is_loop(link->node, belmman_ford) == 0)
	{
		ft_printf("room %s\n", room->room_name);
		ft_printf("link %s\n", link->node);
		return (0);
	}
	else
		return (1);
}
