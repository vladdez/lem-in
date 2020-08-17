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

void print_ht_roomsWithDirection(t_hashtable *ht_rooms)
{
    int i;
    t_node *tmp;
    t_room *tmp2;

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (ht_rooms->room[i] != NULL)
        {
            tmp2 = ht_rooms->room[i];
            while (tmp2)
            {
                if (tmp2->incomingLinks->node != NULL)
                {
                    tmp = tmp2->incomingLinks;
                    while (tmp)
                    {
                        ft_printf("%s->",tmp->node);
                        tmp = tmp->next;
                    }
                }
                ft_printf("%s[%d]", tmp2->room_name, tmp2->bfs_level);
                if (tmp2->outgoingLinks->node != NULL)
                {
                    tmp = tmp2->outgoingLinks;
                    while (tmp)
                    {
                        ft_printf("->%s",tmp->node);
                        tmp = tmp->next;
                    }
                }
                ft_printf("    ");
                tmp2 = tmp2->next;
            }
            ft_printf("\n");
        }
        i++;
    }
    ft_putendl ("End of the hashtable\n");
}

void print_ht_rooms(t_hashtable *ht_rooms)
{
    int i;
    t_node *tmp;
    t_room *tmp2;

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (ht_rooms->room[i] != NULL)
        {
            tmp2 = ht_rooms->room[i];
            while (tmp2)
            {
                ft_printf(" %s[%d]", tmp2->room_name, tmp2->bfs_level);
                if (tmp2->link != NULL)
                {
                    tmp = tmp2->link;
                    while (tmp)
                    {
                        ft_printf("->%s",tmp->node);
                        tmp = tmp->next;
                    }
                }
                tmp2 = tmp2->next;
                ft_printf("    ");
            }
            ft_printf("\n");
        }
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

	i = 0;
	ft_printf("paths\n");
	while (i < path_num)
	{
		if (paths[i] != NULL)
			curr = paths[i];
		while (curr)
		{
			ft_printf("%s-", curr->name);
			curr = curr->next;
		}
        if (paths[i] != NULL)
		    ft_printf("\n");
        i++;
	}
} 