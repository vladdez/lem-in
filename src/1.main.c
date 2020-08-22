/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:00:29 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/19 19:24:33 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_lem_in	*parse(int fd, t_line **input)
{
	t_lem_in	*lem_in;
	t_line		*tmp;

	lem_in = init_lem_in();
	parse_ants(lem_in, fd);
	parse_room(lem_in, fd, input, &tmp);
	parse_link(lem_in, fd, input, &tmp);
	free_input(tmp);
	return (lem_in);
}

int			find_fd(char **av, int ac, int fd)
{
	if (av[1] && (fd = open(av[1], O_RDONLY, 0)) == -1)
	{
		if (fd == -1 && ac == 1)
			fd = 0;
		else
			terminate(ERR_MAP);
	}
	return (fd);
}

void		lem(int fd)
{
	t_lem_in	*lem_in;
	t_line		*input;
	t_queue     *q;
	t_node      *deadlock_name;

	input = NULL;
	lem_in = parse(fd, &input);
	q = bfs(lem_in);
	if (lem_in->end->visit == UNVISITED)
		terminate(ERR_NO_PATH);
	//print_input(input, lem_in->ant_num);
	//print_ht_rooms(lem_in->ht_rooms);
	input_cleaning(lem_in);
	deadlock_name = find_link_direction(lem_in->ht_rooms);
	//print_ht_rooms_with_direction(lem_in->ht_rooms);
	fd = create_paths(lem_in);
	if (fd != 0)
	{
		print_paths(lem_in->paths, lem_in->path_num);
		flow(lem_in, 1, -1);
	}
	free_input(input);
	free_lem_in(lem_in, fd);
	free_queue(q);
	free_deadlocks(deadlock_name);
}

int			main(int ac, char **av)
{
	int fd;

	fd = -1;
	if (ac <= 2)
	{
		fd = find_fd(av, ac, 0);
		lem(fd);
	}
	return (0);
}
