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
	//lem_in->links = NULL;
	return (lem_in);
}

t_lem_in	*parse(char *av, t_line **input)
{
	t_lem_in	*lem_in;
	int			fd;

	fd = open(av, O_RDONLY, 0);
	lem_in = init_lem_in();
	parse_ants(&lem_in, fd);
	parse_room(lem_in, fd, input);

	return (lem_in);
}

void		lem(char *av)
{
	t_lem_in	*lem_in;
	t_line		*input;

	input = NULL;
	lem_in = parse(av, &input);
	printf("ants %d\n", lem_in->ant_num);
	printf("ants_start %d\n", lem_in->ants_start);
			printf("name %d\n", lem_in->rooms->x);

}

int			main(int ac, char **av)
{
	if (ac == 1)
		lem(av[0]);
	if (ac == 2)
		lem(av[1]);
	printf("name");
	return (0);
}
