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

t_hashtable *ht_create()
{
    t_hashtable *ht_rooms;
    int i;

    i = 0;
    if (!(ht_rooms = malloc(sizeof(t_hashtable))))
        terminate(ERR_ALLOCATION);
    if (!(ht_rooms->room = malloc(sizeof(t_room *) * TABLE_SIZE)))
        terminate(ERR_ALLOCATION);
    while (i < TABLE_SIZE)
        ht_rooms->room[i++] = NULL;
    return(ht_rooms);
}

t_coordinate *coordinate_create()
{
    t_coordinate *coordinate;

    if (!(coordinate = malloc(sizeof(t_coordinate))))
        terminate(ERR_ALLOCATION);
    coordinate->room_name = NULL;
    coordinate->x = -1;
    coordinate->y = -1;
    coordinate->next = NULL;
    return (coordinate);
}
t_lem_in	*init_lem_in(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in*)malloc(sizeof(t_lem_in))))
        terminate(ERR_ALLOCATION);
	lem_in->ants_start = 0;
	lem_in->ants_end = 0;
	lem_in->ant_num = 0;
	lem_in->room_num = 0;
	lem_in->path_num = 0;
	lem_in->start = NULL;
	lem_in->end = NULL;
	lem_in->coordinate = coordinate_create();
	lem_in->ht_rooms = ht_create();
	return (lem_in);
}

t_lem_in	*parse(int fd, t_line **input)
{
	t_lem_in	*lem_in;
	t_line      *tmp;

	lem_in = init_lem_in();
	parse_ants(lem_in, fd);
	parse_room(lem_in, fd, input, &tmp);
	parse_link(lem_in, fd, input, &tmp);
	free_input(tmp);
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
	bfs(lem_in);
	if (lem_in->end->visit == UNVISITED)
	    terminate(ERR_NO_PATH);
	print_ht_rooms(lem_in->ht_rooms);
    ImputCleaning(lem_in);
    findLinkDirection(lem_in->ht_rooms);
    print_ht_roomsWithDirection(lem_in->ht_rooms);
	fd = create_paths(lem_in);
	if (fd != 0)                                      // для короткого замыкания
    {
		print_paths(lem_in->paths, lem_in->path_num); // это наглядность путей
	    // flow(lem_in, 1, 2);                         // муравьи
    }
	free_input(input);
	free_lem_in(lem_in);

}

int			main(int ac, char **av)
{
	if (ac <= 2)
		lem(av);
	return (0);
}
