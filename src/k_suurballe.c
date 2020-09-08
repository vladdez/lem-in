//
// Created by Ирина Деева on 07.09.2020.
//

#include "../inc/lem_in.h"



void    algorithm_suurballe(t_lem_in *lem_in, int maxpath)
{
	turn_around_links(lem_in, lem_in->paths[0]);
	//dub_rooms(lem_in, lem_in->paths[0]);
	/*while (maxpath == lem_in)
	{
		algorithm_belmon_ford();
		turn_around(lem_in);
		is_enough();
		count_pathes();
	}*/
}