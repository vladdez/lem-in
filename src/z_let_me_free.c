/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_me_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:02:52 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/19 19:15:55 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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

void	free_queue(t_queue *q)
{
	free(q->room_name);
	free(q);
}

void	free_input(t_line *input)
{
	t_line	*curr;
	t_line	*kill;

	curr = input;
	while (curr)
	{
		kill = curr;
		curr = curr->next;
		free(kill->data);
		free(kill);
	}
	input = NULL;
}

void    free_queue_belmon_ford(t_queue_bf *belmon_ford)
{
	t_queue_bf *kill;

	if (belmon_ford != NULL)
	{
		while (belmon_ford)
		{
			kill = belmon_ford;
			belmon_ford = belmon_ford->next;
			free(kill->room_name);
			free(kill);
		}
	}

}