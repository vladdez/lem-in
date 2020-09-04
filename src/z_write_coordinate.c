/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.7.write_coordinate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:20:06 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/19 17:25:30 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	write_coor(t_coordinate *coordinate, char **words)
{
	t_coordinate	*tmp;
	t_coordinate	*tmp2;

	if (coordinate->room_name == NULL)
	{
		if (!(coordinate->room_name = ft_strdup(words[0])))
			terminate(ERR_ROOM_INIT);
		coordinate->x = ft_atoi(words[1]);
		coordinate->y = ft_atoi(words[2]);
	}
	else
	{
		tmp = coordinate;
		while (tmp->next)
			tmp = tmp->next;
		tmp2 = coordinate_create();
		tmp->next = tmp2;
		if (!(tmp2->room_name = ft_strdup(words[0])))
			terminate(ERR_ROOM_INIT);
		tmp2->x = ft_atoi(words[1]);
		tmp2->y = ft_atoi(words[2]);
	}
}
