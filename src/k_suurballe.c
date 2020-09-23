//
// Created by Ирина Деева on 07.09.2020.
//

#include "../inc/lem_in.h"


void	clean_all_current_pathes(t_path **pa, int path_num)
{
	int		i;
	t_path	*kill;

	i = 0;
	while (i <= path_num)
	{
		if (pa[i] != NULL)
		{
			while (pa[i])
			{
				kill = pa[i];
				pa[i] = pa[i]->next;
				kill->name = NULL;
				free(kill);
			}
		}
		i++;
	}
}


void    count_pathes(t_lem_in *lem_in)
{
	clean_all_current_pathes(lem_in->paths, lem_in->path_num);
	lem_in->path_num = 0;
	//edmon_karts_by_link_price(lem_in);
}

void    algorithm_suurballe(t_lem_in *lem_in, int maxpath)
{
	t_queue_bf *belmon_ford;
	t_path *tmp_path;

	tmp_path = lem_in->paths[0];

	turn_around_links(lem_in, tmp_path );  // поворот по самому короткому 1ому пути
	dub_rooms(lem_in, tmp_path);          // дубль по самому короткому 1ому пути

	belmon_ford = algorithm_belmon_ford(lem_in); // поиск нового пути
	tmp_path = put_belmon_ford_to_the_path(lem_in, belmon_ford); // перенос его в структуру path

	turn_around_links(lem_in, tmp_path); // поворот нового пути
	dub_rooms(lem_in, tmp_path); // дублирование нового пути

	count_pathes(lem_in); // нашли пути из END
	// maxpath or is_enough();

	/*while (maxpath > lem_in)
	{
		algorithm_belmon_ford(lem_in); прошли по  минимальной стоимости до END
	    собрали по ссылкам в очереди путь от start
	    turn_around(lem_in);
		dub_rooms(); при дублирование комнаты сплит линков надо удалить
		count_pathes(); нашли пути из END

	}*/
}