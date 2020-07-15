/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:00:29 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/06 17:03:27 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_lem_in	*init_lem_in(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in*)malloc(sizeof(t_lem_in))))
	{
		return (NULL);                                     // заменить на  terminate(ERR_ALLOCATE) c ошибкой выделения памяти
	}
	lem_in->ants_start = 0;
	lem_in->ants_end = 0;
	lem_in->ant_num = 0;
	lem_in->rooms = NULL;
	lem_in->start = NULL;
	lem_in->end = NULL;
	lem_in->links = NULL;
	lem_in->bfs_length = 0;
	return (lem_in);
}

t_lem_in	*parse(int fd, t_line **input)
{
	t_lem_in	*lem_in;
	t_line		*tmp;

	tmp = NULL;
	lem_in = init_lem_in();
	parse_ants(&lem_in, fd);               // можно через адресс передавать
	parse_room(lem_in, fd, input, &tmp);   // можно через адресс передавать
	if (!lem_in->start || !lem_in->end)    // можно перенести эту проверку в parse_room
		terminate(ERR_START_END_ROOM);
	parse_link(lem_in, fd, input, &tmp);
	if (!lem_in->links)
		terminate(ERR_NO_LINKS);
	free_input(&tmp);
	return (lem_in);
}

void		lem(char **av)
{
	t_lem_in	*lem_in;
	t_line		*input;                  // это наши входные данные строчка за строчкой в структуре
	int			fd;

	input = NULL;
	fd = 0;
	if (av[1] && (fd = open(av[1], O_RDONLY, 0)) == -1) // условие av[1] излишнее и тогда код сокращается до 2х строчек
	{
		if (fd == -1)
			fd = 0;
	}
	lem_in = parse(fd, &input);          // можно через адресс передавать а не двойной указатель
	bfs(lem_in);
	if (lem_in->end->bfs_level == -1)
		terminate(ERR_NO_PATH);
	check_links(lem_in);
	print_input(input, lem_in->ant_num);
	free_input(&input);
	free_lem_in(&lem_in);
	
}

int			main(int ac, char **av)
{
	if (ac <= 2)
		lem(av);                         // сразу подавать аргумент av[1] а не все
	return (0);
}
