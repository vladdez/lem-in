/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:02:35 by kysgramo          #+#    #+#             */
/*   Updated: 2020/06/29 13:02:40 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_line	*create_line(char *line)
{
	t_line *input1;

	if (!(input1 = (t_line *)malloc(sizeof(t_line))))
		terminate(ERR_LINE_INIT);
	input1->data = line;
	input1->next = NULL;
	return (input1);
}

void	link_inputs(t_line **input, t_line *input1)
{
	t_line *current;

	if (*input != NULL)
	{
		current = *input;
		while (current->next)
			current = current->next;
		current->next = input1;
	}
	else
		*input = input1;
}

t_line	*read_line(t_line **input, int fd)
{
	t_line	*input1;
	char	*tmp;
	int		size;

	input1 = NULL;
	if ((size = get_next_line(fd, &tmp) > 0))
	{
		input1 = create_line(tmp);
		link_inputs(input, input1);
	}
	if (size == -1)
		terminate(ERR_READING);
	return (input1);
}
