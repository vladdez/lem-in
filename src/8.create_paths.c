/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.create_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:40:02 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/31 14:30:37 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		is_short_circuit(t_lem_in *lem_in)
{
	t_node	*cur;
	int		p;

	p = 0;
	cur = lem_in->start->link;
	while (cur)
	{
		if (!ft_strcmp(cur->node, lem_in->end->room_name))
		{
			ft_printf("\nL%s-%s \n", lem_in->start->room_name, lem_in->end->room_name); // переделать печать здесь
			return (0);
		}
		else
			cur = cur->next;
		p++;          // count of nodes
	}
	return (p);
}

int		len_nei(t_node *n)
{
	int		len;
	t_node	*curr;

	len = 0;
	curr = n;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}

t_path	*create_one_path(t_room *cur)
{
	t_path *pa;

	if (!(pa = (t_path *)ft_memalloc(sizeof(t_path))))
		terminate(ERR_PATH_INIT);
	pa->name = ft_strdup(cur->room_name);
	pa->len = -1;
	pa->ant_index = 0;
	pa->head = 0;
	return (pa);
}

t_room 	*find_lowest_bfs(t_node *n, t_hashtable *ht_rooms)
{
	t_node	*cur;
	t_room  *TmpRoom;
    t_room  *LowestBfsRoom;
	int		lowest;
	int		level;

	lowest = 2147483647;
	cur = n;
    LowestBfsRoom = NULL;
	while (cur)
	{
        TmpRoom = FindRoomInHashtable(cur->node, ht_rooms);
		if (TmpRoom->visit2 == UNVISITED)
		{
			level = TmpRoom->bfs_level;
			if (level < lowest)
			{
				lowest = level;
                LowestBfsRoom = TmpRoom;
			}
		}
		cur = cur->next;
	}
	return (LowestBfsRoom);
}


t_room 	*find_best_room(t_room *cur, t_hashtable *ht_rooms)
{
    t_room *tmp;

	if ((len_nei(cur->link) == 1))
        return(FindRoomInHashtable(cur->link->node, ht_rooms));// если один сосед то сразу ее, в текущем коде сюда не заходит
	else
		tmp = find_lowest_bfs(cur->link, ht_rooms); // иначе по  наименьшему bfs
	return (tmp);
}


void    DeleteCurrentPath(t_path *path)
{
    t_path *tmp;

    tmp = path;
    while (tmp)
    {
        tmp = path->next;
        free(path);
        path = tmp;
    }

}

void	create_way(t_lem_in *lem_in, int cut, int j)
{
	t_room	*cur;
	t_path	*tmp;
	int		len;
	t_room *TmpRoom;

	tmp = NULL;
	while (j < cut) // перебор путей по массиву
	{
		len = 0;
		cur = lem_in->end;
		lem_in->paths[j] = create_one_path(lem_in->end);  // инизализация, важно что первый  это END
		while (cur != lem_in->start)                      // засись команты в путь по связному списку
		{
			TmpRoom = find_best_room(cur, lem_in->ht_rooms);
			if (TmpRoom == lem_in->end || TmpRoom == NULL)
            {
			    DeleteCurrentPath(lem_in->paths[j]);
                lem_in->paths[j] = NULL;
                lem_in->path_num--;
			    break;
            }
			if (TmpRoom != lem_in->start)
                TmpRoom->visit2 = VISITED;
			cur = TmpRoom;                 // добавить поиск комнаты по i
			tmp = create_one_path(cur);   // указатель где начинается путь
			tmp->next = lem_in->paths[j];
			lem_in->paths[j] = tmp;
			len++;
			tmp = NULL;

		}
		if (lem_in->paths[j])
		    lem_in->paths[j]->len = len;      // !!! здесь потенциальная ошибка так как можем пропустить путь, они не записываются друг за другом
		j++;
	}
}

int		create_paths(t_lem_in *lem_in)
{
	int		cut_s;
	int		cut_e;
	int		cut;
	int		i;

	i = 0;
	cut_s = is_short_circuit(lem_in);   // короткое замыкание и протестировать что во free не уходит стурктура путей
	if (cut_s != 0)
	{
		cut_e = len_nei(lem_in->end->link);
		cut = cut_e > cut_s ? cut_s : cut_e; // мак число путей
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (cut + 1));  // проверить без 1
		while (i < cut + 1)
			lem_in->paths[i++] = NULL;
		lem_in->path_num = cut; // мак число путей
		create_way(lem_in, cut, 0);
	}
	return (cut_s); // мы это отправлает по делу чтобы отследить короткое замыкание
}
