#include "lem-in.h"

t_lem_in	*init_lem_in()
{
	t_lem_in	*lem_in;

    if (!(lem_in = (t_lem_in*)malloc(sizeof(t_lem_in))))
	{
		return (NULL);
	}
	lem_in->ants_start = 0;
	lem_in->ants_end = 0;
	lem_in->ant_num = 0;
	return (lem_in);
}


t_lem_in 	*parse(char *av, t_line *input)
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
	t_line		**input;

	if (!(input = (t_line*)(malloc(sizeof(t_line)))))
		return (NULL);
	lem_in = parse(av, &input);
	printf("ants %d\n", lem_in->ant_num);
}

int			main(int ac, char **av)
{
	errno = 0;
	if (ac == 1)
		lem(av[0]);	
	if (ac == 2)
		lem(av[1]);
	return (0);
}