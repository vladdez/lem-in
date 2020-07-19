/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:01:31 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/07 18:04:01 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_nei	*create_q_elem(t_room *room)
{
	t_nei	*q;
	t_nei	*curr;
	t_nei	*nei;

	curr = NULL;
	nei = NULL;
	if (!(q = (t_nei *)ft_memalloc(sizeof(t_nei *))))
		terminate(ERR_QUEUE_INIT);
	q->to = ft_strdup(room->name);
	q->next = NULL;
	//q->b = 0;
	curr = q;
	nei = room->nei;
	//printf("-%s\n", nei->to);
	while (nei)
	{
		if (!(curr->next = (t_nei *)ft_memalloc(sizeof(t_nei *))))
			terminate(ERR_QUEUE_INIT);

		curr = curr->next;
		curr->to = ft_strdup(nei->to);
		//curr->b = 0;
		curr->next = NULL;
		//printf("+%s\n", curr->to);
		//printf("+%s\n", nei->to);
		nei = nei->next;
		
	}
	return (q);
}

t_nei	*add_nei(t_room *room)
{
	t_nei	*q;
	t_nei	*curr;
	t_nei	*nei;

	nei = room->nei;
	q = NULL;
	if (nei)
	{
		if (!(q = (t_nei *)ft_memalloc(sizeof(t_nei *))))
			terminate(ERR_QUEUE_INIT);
		q->to = ft_strdup(nei->to);
		q->next = NULL;
		//q->b = 0;
		curr = q;
		while (nei)
		{
			if (!(curr->next = (t_nei *)ft_memalloc(sizeof(t_nei *))))
				terminate(ERR_QUEUE_INIT);
			curr = curr->next;
			curr->to = ft_strdup(nei->to);
			//curr->b = 0;
			//printf("+%s\n", curr->to);
			curr->next = NULL;
			nei = nei->next;
		}
	}
	return (q);
}

t_room		*find_room(t_room *room, char *name)
{
	int i;
	t_room *tmp;

	i = 0;
	if (!ft_strcmp(room->name, name))
		 return(room);
	else
	{
		tmp = room;
		while (tmp)
		{
			if (!ft_strcmp(room->name, name))
				return(tmp);
			else
				tmp = tmp->next;
		}
	}
	return (NULL);
}

void	bfs(t_lem_in *lem_in)
{
	t_nei	*curr;
	t_nei	*q;
	t_nei	*tail;
	t_room	*room;
	int		i;
	int		len;

	len = 0;
	q = NULL;
	lem_in->start->bfs_level = 0;
	q = create_q_elem(lem_in->start);
	curr = q;
	tail = q;
	while (curr->next != NULL)
	{
        curr = curr->next;
		i = hash_fun(curr->to);
		while (tail->next != NULL)
			tail = tail->next;
		room = find_room(lem_in->hash_table[i], curr->to);
		len = room->bfs_level;
		tail->next = add_nei(room);
		if ((ft_strcmp(curr->to, lem_in->end->name)))
		{
			room->bfs_level = len;
			lem_in->bfs_length = len;          
		}
		else
			lem_in->end->bfs_level = 2147483647;
	}
	free_nei(&q);
}
