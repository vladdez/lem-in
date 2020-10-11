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

#include "../inc/lem_in.h"

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
	fd = 0;
	if (ac >= 2 && av[1][0] != '-')
		fd = open(av[1], O_RDONLY);
	return (fd);
}

void		ft_bonus(t_lem_in *lem_in, int fd, char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-p") && fd != 0)
			print_paths(lem_in->paths, lem_in->path_num);
		else if (ft_strequ(av[i], "-r"))
			print_ht_rooms(lem_in->ht_rooms);
		else if (ft_strequ(av[i], "-rd"))
			print_ht_rooms_with_direction(lem_in->ht_rooms);
		else if (ft_strequ(av[i], "-l"))
			ft_printf("\nLines printed: %d\n", lem_in->lines);
		i++;
	}
}

void		lem(int fd, char **av, int ac)
{
	t_lem_in	*lem_in;
	t_line		*input;

	input = NULL;
	lem_in = parse(fd, &input);
	bfs(lem_in);
	if (lem_in->end->bfs_visit != lem_in->bfs_used)
		terminate(ERR_NO_PATH);
	find_link_direction(lem_in->ht_rooms);
	print_input(input, lem_in->ant_num);
	fd = create_paths(lem_in);
	if (fd != 0)
		flow(lem_in, 1, -1);
	if (ac >= 2)
		ft_bonus(lem_in, fd, av, ac);
	free_all(input, lem_in, fd);
}

int			main(int ac, char **av)
{
	int fd;

	fd = -1;
	fd = find_fd(av, ac, 0);
	lem(fd, av, ac);
	return (0);
}
