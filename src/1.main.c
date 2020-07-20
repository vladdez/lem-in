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
		terminate(ERR_ALLOCATION);
	lem_in->ants_start = 0;
	lem_in->ants_end = 0;
	lem_in->ant_num = 0;
	lem_in->rooms = NULL;
	lem_in->start = NULL;
	lem_in->links = NULL;
	lem_in->end = NULL;
	lem_in->bfs_length = 0;
	return (lem_in);
}

t_lem_in	*parse(int fd, t_line **input)
{
	t_lem_in	*lem_in;
	t_line		*tmp;

	tmp = NULL;
	lem_in = init_lem_in();
	parse_ants(lem_in, fd);
	create_hash_table(lem_in);
	
	parse_room(lem_in, fd, input, &tmp);
	if (!lem_in->start || !lem_in->end)
		terminate(ERR_START_END_ROOM);
	parse_link(lem_in, fd, input, &tmp);
	free_input(&tmp);
	return (lem_in);
}

void print_list(t_room *t)
{
	t_nei	*n;

	while (t)
	{
		printf("%s[%d]->", t->name, t->bfs_level);
		if (t->nei)
		{
			n = t->nei;
			while (n)
			{
				printf("(%s->)", n->to);
				n = n->next;
			}
		}

		t = t->next;
	}
	printf("\n");
}

void print_ht(t_room **gr)
{
	int i;

	i = 0;
	while (i < TABLEN)
	{
		if (gr[i] == NULL)
			printf("NULL\n");
		else
			print_list(gr[i]);
		i++;
	}
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
	if (lem_in->end->bfs_level == -1)
		terminate(ERR_NO_PATH);
	align_links(lem_in);
	print_ht(lem_in->hash_table);
	/*check_links(lem_in);*/
	print_input(input, lem_in->ant_num);
	/*loo_rooms(&lem_in->rooms);
	loo_links(&lem_in->links);*/

	free_input(&input);
	free_lem_in(&lem_in);
	
}

int			main(int ac, char **av)
{
	if (ac <= 2)
		lem(av);
	return (0);
}
