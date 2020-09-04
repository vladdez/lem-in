/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.8.dashes_in_imput.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:26:02 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/20 19:03:09 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		count_dashes_in_imput(char *str)
{
	int		dashes_number;

	dashes_number = 0;
	while (*str)
	{
		if (*str == '-')
			dashes_number++;
		str++;
	}
	return (dashes_number);
}

void	start_toward_for_dashes_imput(t_lem_in *lem_in, char *str)
{
	t_coordinate	*tmp;
	char			*d;
	char			*start;
	char			*toward;

	tmp = lem_in->coordinate;
	while (tmp)
	{
		if ((d = ft_strnstr(str,
						tmp->room_name, ft_strlen(tmp->room_name))) != NULL)
		{
			if (!(start = ft_strsub(str, 0, ft_strlen(tmp->room_name))))
				terminate(ERR_LINK_INIT);
			d = d + ft_strlen(tmp->room_name) + 1;
			if (!(toward = ft_strdup(d)))
				terminate(ERR_LINK_INIT);
			find_start_room(lem_in->ht_rooms, start, toward);
			return ;
		}
		else
			tmp = tmp->next;
	}
	terminate(ERR_LINK_PARSING);
}
