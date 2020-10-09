/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_suurballe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:36:56 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:37:11 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		create_way_sub_with_price(t_lem_in *lem_in,
t_path *tmp, t_room *cur, int j)
{
	t_room	*tmp_room;
	int		len;

	len = 0;
	while (cur != lem_in->start)
	{
		tmp_room = find_best_link_with_price(cur->link, lem_in->ht_rooms);
		if (tmp_room == lem_in->end || tmp_room == NULL)
		{
			delete_current_path(lem_in->paths[j]);
			lem_in->paths[j] = NULL;
			return (-1);
		}
		cur = tmp_room;
		tmp = create_one_path(cur);
		tmp->next = lem_in->paths[j];
		lem_in->paths[j] = tmp;
		tmp = NULL;
		len++;
	}
	lem_in->start->ek_visit = UNVISITED;
	return (len);
}

int		find_posible_ways_number(t_node *link)
{
	int i;

	i = 0;
	while (link)
	{
		if (link->direction == DOWNSTREAM)
			i++;
		link = link->next;
	}
	return (i);
}

void	count_pathes(t_lem_in *lem_in)
{
	clean_all_edmon_karts_marks(lem_in);
	clean_all_current_pathes(lem_in->paths, lem_in->path_num);
	lem_in->path_num = 0;
	edmon_karts_by_link_price(lem_in);
}

int		check_found_way(t_queue_bf *belmon_ford)
{
	if (belmon_ford == NULL)
		return (1);
	else
		return (0);
}

void	algorithm_suurballe(t_lem_in *lem_in, int *maxpath)
{
	t_queue_bf	*belmon_ford;
	t_path		*tmp_path;

	clean_all_edmon_karts_marks_in_all_ht(lem_in->ht_rooms);
	tmp_path = lem_in->paths[0];
	turn_around_links(lem_in, tmp_path);
	dub_rooms(lem_in, tmp_path);
	clean_all_current_pathes(lem_in->paths, lem_in->path_num);
	while (*maxpath > lem_in->path_num)
	{
		belmon_ford = algorithm_belmon_ford(lem_in);
		if (check_found_way(belmon_ford) == 1)
			break ;
		tmp_path = put_belmon_ford_to_the_path(lem_in, belmon_ford);
		free_queue_belmon_ford(belmon_ford);
		turn_around_links(lem_in, tmp_path);
		dub_rooms(lem_in, tmp_path);
		free_found_path(tmp_path);
		count_pathes(lem_in);
		if (is_enough(lem_in) == 1)
			break ;
	}
}
/*
**  чистить до модификации так как потом комнат такого типа не будет
** а будет IN OUT IN_OUT
** поворот по самому короткому 1ому пути
** дубль по самому короткому 1ому пути
** поиск нового пути
** перенос его в структуру path
** free the bf_queue
** поворот нового пути	поворот после второго пути и удаляется не та линка
** дублирование нового пути
** нашли пути из END
*/
