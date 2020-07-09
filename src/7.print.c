/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:22:58 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/09 19:23:03 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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
}
