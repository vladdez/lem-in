/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_me_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:02:52 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/07 18:31:30 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_strsplit_free(char ***strsplit)
{
	char	**curr;

	if (strsplit && *strsplit)
	{
		curr = ((*strsplit));
		while ((*curr))
			free((*(curr++)));
		free((*strsplit));
		(*strsplit) = NULL;
	}
}

void	free_rooms(t_room **sentenced)
{
	t_room *kill;

	if (sentenced)
		while ((*sentenced))
		{
			kill = (*sentenced);
			(*sentenced) = (*sentenced)->next;
			free(kill->name);
			free(kill);
		}
}

void	free_nei(t_nei **sentenced)
{
	t_nei *kill;

	if (sentenced)
		while ((*sentenced))
		{
			kill = (*sentenced);
			(*sentenced) = (*sentenced)->next;
			free(kill->to);
			free(kill);
		}
}

void	free_ht(t_room **ht)
{
	int i;
	t_room *kill;

	i = 0;
	while (i < TABLEN)
	{
		if (ht[i] != NULL)
		{
			while (ht[i])
			{
				kill = ht[i];
				ht[i] = ht[i]->next;
				free(kill->name);
				free_nei(&kill->nei);
				free(kill);
			}
		}
		i++;
	}
	free(ht);
} 

void	free_lem_in(t_lem_in **lem_in)
{
	if (lem_in && *lem_in)
	{
		free_rooms(&(*lem_in)->rooms);
		free_ht((*lem_in)->hash_table);
		free((*lem_in));
		(*lem_in) = NULL;
	}
}

void	free_input(t_line **input)
{
	t_line	*curr;
	t_line	*kill;

	curr = *(input);
	while (curr)
	{
		kill = curr;
		curr = curr->next;
		free(kill->data);
		free(kill);
	}
	*input = NULL;
}