#include "lem-in.h"

void	free_paths(t_path **pa, int path_num)
{
	int i;
	t_path *kill;

	i = 1;

	while (i <= path_num)
	{
		if (pa[i] != NULL)
		{
			while (pa[i])
			{
				kill = pa[i];
                pa[i] = pa[i]->next;
				free(kill->name);
				free(kill);
			}
		}
		i++;
	}
	if (pa != NULL)
	    free(pa);
} 

void	free_node(t_node **sentenced)
{
	t_node *kill;

	if (sentenced)
		while ((*sentenced))
		{
			kill = (*sentenced);
			(*sentenced) = (*sentenced)->next;
			free(kill->node);
			kill->node = NULL;
			free(kill);
			kill = NULL;
		}
}

void	free_ht(t_room **ht)
{
	int i;
	t_room *kill;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (ht[i] != NULL)
		{
			while (ht[i])
			{
				kill = ht[i];
				ht[i] = ht[i]->next;
				free(kill->room_name);
				free_node(&kill->link);
				free(kill);
			}
		}
		i++;
	}
	free(ht);
} 

void	free_coord(t_coordinate **input)
{
	t_coordinate	*curr;
	t_coordinate	*kill;

	curr = *input;
	while (curr)
	{
		kill = curr;
		curr = curr->next;
		free(kill->room_name);
		free(kill);
	}
	input = NULL;
}

void    free_lem_in(t_lem_in *lem_in)
{
	if (lem_in)
	{
        free_ht(lem_in->ht_rooms->room);
        free(lem_in->ht_rooms);
		free_coord(&(lem_in->coordinate));
		free_paths(lem_in->paths, lem_in->path_num);
		free(lem_in);
		(lem_in) = NULL;
	}
}