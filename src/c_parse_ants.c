/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.1_parse_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:09:32 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/19 17:09:38 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	parse_ants(t_lem_in *lem_in, int fd)
{
	char		*line;

	line = NULL;
	if ((get_next_line(fd, &line)) > 0)
	{
		if (ft_isint(line) == 1)
		{
			lem_in->ant_num = ft_atoi(line);
			if (lem_in->ant_num <= 0)
				terminate(ERR_ANTS_NUM_PARSING);
		}
		else
			terminate(ERR_ANTS_NUM_PARSING);
		free(line);
	}
	else
		terminate(ERR_ANTS_NUM_PARSING);
}
