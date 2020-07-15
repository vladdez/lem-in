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
