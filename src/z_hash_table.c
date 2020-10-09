/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.5.hash_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 18:57:52 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/21 12:14:52 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		sum_ascii(char *room_name)
{
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	while (room_name[i] != '\0')
	{
		sum += (int)(room_name[i]) * 49;
		i++;
	}
	return (sum % TABLE_SIZE);
}

t_room	*find_room_with_type_in_hashtable(char *room_name,
int typeroom, t_hashtable *ht_rooms)
{
	int		i;
	t_room	*tmp;

	i = sum_ascii(room_name);
	tmp = ht_rooms->room[i];
	while (tmp)
	{
		if (ft_strcmp(tmp->room_name, room_name) == 0 &&
		(tmp->in_out == typeroom))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_room	*find_room_in_hashtable(char *room_name, t_hashtable *ht_rooms)
{
	int		i;
	t_room	*tmp;

	i = sum_ascii(room_name);
	tmp = ht_rooms->room[i];
	while (ft_strcmp(tmp->room_name, room_name) != 0)
		tmp = tmp->next;
	return (tmp);
}

t_node	*find_room_links(char *current_room_name, t_hashtable *ht_rooms)
{
	int		i;
	t_room	*tmp;

	i = sum_ascii(current_room_name);
	tmp = ht_rooms->room[i];
	while (ft_strcmp(tmp->room_name, current_room_name) != 0)
		tmp = tmp->next;
	return (tmp->link);
}
