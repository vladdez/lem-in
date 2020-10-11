/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_me_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:02:52 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:02:50 by kysgramo         ###   ########.fr       */
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
