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

void print_ht_rooms(t_hashtable *ht_rooms)
{
    int i;
    t_node *tmp;

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (ht_rooms->room[i] != NULL)
        {
            ft_printf("%s [%d]", ht_rooms->room[i]->room_name, ht_rooms->room[i]->bfs_level);
            if (ht_rooms->room[i]->link != NULL)
            {
                tmp = ht_rooms->room[i]->link;
                while (tmp)
                {
                    ft_printf("->%s",tmp->node);
                    tmp = tmp->next;
                }
            }
            ft_printf("\n");
        }
        // else
        //     ft_printf("NULL");
        
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


void print_paths(t_path **paths, int path_num)
{
	t_path *curr;
	int		i;

	i = 1;
	ft_printf("paths\n");
	while (i <= path_num)
	{
		if (paths[i] != NULL)
			curr = paths[i];
		while (curr)
		{
			ft_printf("%s-", curr->name);
			curr = curr->next;
		}
		curr = NULL;
		i++;
		ft_printf("\n");
	}
	
} 