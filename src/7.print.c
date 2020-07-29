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

void print_hash_table(t_hashtable *hash_table)
{
    int i;
    t_node *tmp;

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (hash_table->room[i] != NULL)
        {
            ft_printf("%s [%d]", hash_table->room[i]->name, hash_table->room[i]->bfs_level);
            if (hash_table->room[i]->link != NULL)
            {
                tmp = hash_table->room[i]->link;
                while (tmp)
                {
                    ft_printf("->%s",tmp->node);
                    tmp = tmp->next;
                }
            }
        }
        else
            ft_printf("NULL");
        ft_printf("\n");
        i++;
    }
    ft_putendl ("End of the hashtable\n");
}


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
