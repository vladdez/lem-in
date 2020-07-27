/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.create_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:40:02 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/15 17:40:06 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"


int		is_short_circuit(t_lem_in *lem_in)
{
	t_nei *cur;
	int p;

	p = 0;

	cur = lem_in->start->output_nei;
	while (cur)
	{
		if (!ft_strcmp(cur->to, lem_in->end->name))
		{
			ft_printf("\nL%s-%s \n", lem_in->start->name, lem_in->end->name);
				return (0);
		}
		else
			cur = cur->next;
		p++;
	}
	return (p);
}

int		len_nei(t_nei *n)
{
	int 	len;
	t_nei 	*curr;

	len = 0;
	curr = n;
	while (curr)
	{
		len++;
		curr = curr->next;
	}

	return (len);
}

int		find_lowest_bfs(t_nei *n, t_room **hash_table)
{
	t_nei 	*curr;
	int		lowest;
	int		i;
	int		tmp;
	int		r;

	lowest = 2147483647;
	curr = n;
	r = 0;
	i = 0;
	while (curr)
	{		
		i = hash_fun(curr->to);
		if (hash_table[i]->visited != 1)
		{	
			tmp = hash_table[i]->bfs_level;
			if (tmp < lowest)
			{
				lowest = tmp;
				r = i;
			}
		}
		curr = curr->next;
	}
	return (r);
}

int		find_best_room(t_room *cur, t_room **hash_table)
{
	int i;

	i = 0;
	if ((len_nei(cur->input_nei) == 1))
		i = hash_fun(cur->input_nei->to);
	else
		i = find_lowest_bfs(cur->input_nei, hash_table);
	return (i);
}


t_path	*create_one_path(t_room *cur)
{
	t_path *pa;

	if (!(pa = (t_path *)ft_memalloc(sizeof(t_path))))
		terminate(ERR_PATH_INIT);	
	pa->name = ft_strdup(cur->name);
    return (pa);
}

void	create_way(t_lem_in *lem_in, int cut)
{
	t_room *cur;
	t_path	*tmp;
	int		len;
	int		i;
	int		j;

	j = 1;
	i = 0;
	tmp = NULL;
	while (j <= cut)
	{
		len = 0;
		cur = lem_in->end;
    	lem_in->paths[j] = create_one_path(lem_in->end);
		while (cur != lem_in->start)
		{
			i = find_best_room(cur, lem_in->hash_table);
			if (lem_in->hash_table[i] != lem_in->start	&&
			lem_in->hash_table[i] != lem_in->end)
				lem_in->hash_table[i]->visited = 1;
			cur = lem_in->hash_table[i];
			tmp = create_one_path(cur);
			tmp->next = lem_in->paths[j];
			lem_in->paths[j] = tmp;
			len++;
			tmp = NULL;
		}
		lem_in->paths[j]->len = len;
		j++;
	}
}

void	create_paths(t_lem_in *lem_in)
{
	int 	cut_s;
	int 	cut_e;
	int		cut;
	int		i;
	t_room 	*cur;

	i = 0;
	cur = lem_in->start;
	cut_s = is_short_circuit(lem_in);
	if (cut_s != 0)
	{
		cut_e = len_nei(lem_in->end->input_nei);
		cut = cut_e > cut_s ? cut_s : cut_e;
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (cut +1));
		while (i < (cut+ 1))
			lem_in->paths[i++] = NULL;
		lem_in->path_num = cut;
		create_way(lem_in, cut);
	



	}
}