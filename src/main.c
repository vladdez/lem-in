/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:00:29 by kysgramo          #+#    #+#             */
/*   Updated: 2020/06/29 13:00:39 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_lem_in	*init_lem_in(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in*)malloc(sizeof(t_lem_in))))
	{
		return (NULL);
	}
	lem_in->ants_start = 0;
	lem_in->ants_end = 0;
	lem_in->ant_num = 0;
	lem_in->rooms = NULL;
	lem_in->start = NULL;
	lem_in->end = NULL;
	lem_in->links = NULL;
	return (lem_in);
}

t_lem_in	*parse(int fd, t_line **input)
{
	t_lem_in	*lem_in;
	t_line		*line;

	lem_in = init_lem_in();
	parse_ants(&lem_in, fd);
	parse_room(lem_in, fd, input, &line);
	if (!lem_in->start || !lem_in->end)
		terminate(ERR_START_END_ROOM);
	parse_link(lem_in, fd, input, &line);
	if (!lem_in->links)
		terminate(ERR_NO_LINKS);
	return (lem_in);
}

void		lem(char **av)
{
	t_lem_in	*lem_in;
	t_line		*input;
	int			fd;

	input = NULL;
	fd = 0;
	if (av[1] && (fd = open(av[1], O_RDONLY, 0)) == -1)
	{
		if (fd == -1)
			fd = 0;
	}
	lem_in = parse(fd, &input);
}

int			main(int ac, char **av)
{
	if (ac <= 2)
		lem(av);	
	return (0);
}
