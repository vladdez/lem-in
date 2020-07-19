valgrind --leak-check=full ./lem-in < maps/error/rooms/multiple_starts.map
valgrind --leak-check=full ./lem-in < coordinates_duplicate.map  
valgrind --leak-check=full ./lem-in < multiple_starts.map        
valgrind --leak-check=full ./lem-in < name_with_L.map            
valgrind --leak-check=full ./lem-in < no_end_room.map            
valgrind --leak-check=full ./lem-in < no_start_room.map          
valgrind --leak-check=full ./lem-in < multiple_ends.map          
valgrind --leak-check=full ./lem-in < name_duplicate.map         
valgrind --leak-check=full ./lem-in < name_with_octothorpe.map   
valgrind --leak-check=full ./lem-in < no_rooms.map 

valgrind --leak-check=full ./lem-in < maps/valid/difficult/one_name_with_dashes.map   
valgrind --leak-check=full ./lem-in < three_ways.map             
valgrind --leak-check=full ./lem-in < two_names_with_dashes.map

valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/1.map 
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/2.map  
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/3.map  
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/4.map  
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/5.map 
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/6.map  
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/7.map  
valgrind --leak-check=full ./lem-in < maps/valid/vs/multiple_ways/8.map

valgrind --leak-check=full ./lem-in < maps/valid/vs/one_way/1.map
valgrind --leak-check=full ./lem-in < maps/valid/vs/one_way/2.map
valgrind --leak-check=full ./lem-in < maps/valid/vs/one_way/3.map
valgrind --leak-check=full ./lem-in < maps/valid/vs/one_way/4.map
valgrind --leak-check=full ./lem-in < maps/valid/vs/one_way/5.map

t_queue	*create_q_elem(t_room *room)
{
	t_queue *q;

	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue *))))
		terminate(ERR_QUEUE_INIT);
	q->room = room;
	q->next = NULL;
	return (q);
}

void	add_q_elem(t_queue **q, t_queue	*elem)
{
	t_queue	*curr;

	if (q && *q)
	{
		curr = *q;
		while (curr->next)
			curr = curr->next;
		curr->next = elem;
	}
	else if (elem)
		*q = elem;
}

void	enqueue(t_lem_in *lem_in, t_queue **q, t_room *room)
{
	t_link *curr;

	curr = lem_in->links;
	while (curr)
	{
		if (curr->start == room)
		{
			if (curr->end->bfs_level == -1)
			{
				curr->end->bfs_level = room->bfs_level + 1;
				add_q_elem(q, create_q_elem(curr->end));
			}
		}
		else if (curr->end == room)
		{
			if (curr->end->bfs_level == -1)
			{
				curr->end->bfs_level = room->bfs_level + 1;
				add_q_elem(q, create_q_elem(curr->start));
			}
		}
		curr = curr->next;
	}
}

t_queue	*first_elem(t_queue **q)
{
	t_queue	*curr;

	curr = NULL;
	if (q && *q)
	{
		curr = *q;
		*q = (*q)->next;
	}
	return (curr);
}