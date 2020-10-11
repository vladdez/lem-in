/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.6.init_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:19:52 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/20 19:02:06 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room	*create_room(t_coordinate *coordinate, char *tmp)
{
	t_room	*room;
	char	**words;

	if (!(words = ft_strsplit(tmp, ' ')))
		terminate(ERR_ROOM_INIT);
	if (!(room = (t_room *)malloc(sizeof(t_room))))
		terminate(ERR_ROOM_INIT);
	if (!(room->room_name = ft_strdup(words[0])))
		terminate(ERR_ROOM_INIT);
	write_coor(coordinate, words);
	room->in_out = IN_OUT;
	room->bfs_visit = UNVISITED;
	room->ek_visit = UNVISITED;
	room->bfs_level = -1;
	room->next = NULL;
	room->link = neighbour_init();
	room->outgoing_links = neighbour_init();
	room->incoming_links = neighbour_init();
	room->cut = UNCUT;
	ft_strsplit_free(&words);
	return (room);
}

t_node	*neighbour_init(void)
{
	t_node	*link;

	if (!(link = malloc(sizeof(t_node) * 1)))
		terminate(ERR_ALLOCATION);
	link->node = NULL;
	link->price = ONE;
	link->type_room = IN_OUT;
	link->direction = BOTH_STREAM;
	link->next = NULL;
	return (link);
}

t_queue	*create_queue(int room_num)
{
	t_queue	*q;
	int		i;

	i = 0;
	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue))))
		terminate(ERR_ALLOCATION);
	if (!(q->room_name = malloc(sizeof(t_room *) * (room_num + 1))))
		terminate(ERR_ALLOCATION);
	while (i < room_num)
		q->room_name[i++] = NULL;
	q->toward = -1;
	q->from = -1;
	return (q);
}
