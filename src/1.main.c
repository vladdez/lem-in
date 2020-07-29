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
    t_hashtable *hash_table;
    int i;

    i = 0;
    if (!(hash_table = malloc(sizeof(t_hashtable))))
        terminate(ERR_ALLOCATION);
    if (!(hash_table->room = malloc(sizeof(t_room *) * TABLE_SIZE)))
        terminate(ERR_ALLOCATION);
    while (i < TABLE_SIZE)
        hash_table->room[i++] = NULL;
    return(hash_table);
}

t_coordinate *coordinate_create()
{
    t_coordinate *coordinate;

    if (!(coordinate = malloc(sizeof(t_coordinate))))
        terminate(ERR_ALLOCATION);
    coordinate->name = NULL;
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
	lem_in->ant_num = 0;
	lem_in->room_num = 0;
	lem_in->start = NULL;
	lem_in->end = NULL;
	lem_in->coordinate = coordinate_create();
	lem_in->bfs_length = 0;
	lem_in->hash_table = ht_create();
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

void		lem(char *av)
{
	t_lem_in	*lem_in;
	t_line		*input;                  // это наши входные данные строчка за строчкой в структуре
	int			fd;

	input = NULL;
	if ((fd = open(av, O_RDONLY, 0)) == -1)
	    fd = 0;
	lem_in = parse(fd, &input);
	bfs(lem_in);
	//if (lem_in->end->visit == -1)
	 //   terminate(ERR_NO_PATH);
	//check_links(lem_in);
	print_hash_table(lem_in->hash_table);
	print_input(input, lem_in->ant_num);
	free_input(input);
	free_lem_in(lem_in);

}

int			main(int ac, char **av)
{
	if (ac <= 2)
		lem(av[1]);
	return (0);
}
