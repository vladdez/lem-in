/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:22:58 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/21 12:03:03 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_input(t_line *input, int n)
{
	t_line *curr;

	curr = input;
	ft_printf("%d\n", n);
	while (curr)
	{
		ft_putendl(curr->data);
		curr = curr->next;
	}
	ft_printf("\n");
}

void	print_paths(t_path **paths, int path_num)
{
	t_path	*curr;
	int		i;

	i = 0;
	ft_printf("LAYERED NETWORK:\n\n");
	while (i < path_num)
	{
		if (paths[i] != NULL)
			curr = paths[i];
		ft_printf("{green}way %d, lenght %d:{eoc}\n", i, curr->len);
		while (curr)
		{
			if (curr != paths[i])
				ft_printf("{red}->{eoc}");
			ft_printf("{red}%s{eoc}", curr->name);
			curr = curr->next;
		}
		if (paths[i] != NULL)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}
