/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:03:30 by kysgramo          #+#    #+#             */
/*   Updated: 2020/06/29 13:03:33 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

typedef struct			s_line
{
	char				*data;
	struct s_line		*next;
}						t_line;

typedef struct			s_node
{
    char				*node;
	int					type;
    struct s_node		*next;
}						t_node;

typedef struct			s_room
{
	char				*room_name;
	int					visit;
	int					visit2;
	int					bfs_level;
	t_node              *link;
	t_node              *outgoingLinks;
    t_node              *incomingLinks;
	int					input_links;
	int					output_links;
	struct s_room		*next;
}						t_room;

typedef struct          s_hashtable
{
    t_room              **room;
}                       t_hashtable;

typedef struct          s_coordinate
{
    char                *room_name;
    int					x;
    int					y;
    struct s_coordinate *next;
}                       t_coordinate;

typedef struct			s_path
{
	int					len;
	int					ant_index;
	int					head;
	char				*name;
	struct s_path		*next;
}						t_path;

typedef struct			s_lem_in
{
	int					ants_start;
	int					ants_end;
	int                 room_num;
	int					path_num;
	int					ant_num;
	t_room				*start;
	t_room				*end;
	t_coordinate        *coordinate;
	t_hashtable         *ht_rooms;
	t_path				**paths;
}						t_lem_in;

typedef struct			s_queue
{
	char				**room_name;
	int                 toward;
	int       		    from;
}						t_queue;


int						main(int ac, char **av);
void					*terminate(char *er);

void					parse_ants(t_lem_in *lem_in, int fd);
void					parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp);
void					parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp);
t_node					*neighbour_init();
t_coordinate			*coordinate_create();

int						is_room(char *str);
int						is_comment(char *str);
int						ft_isint(char *tmp);
int						is_command(char *str);
int						iswhat(char *str);


t_line					*read_line(t_line **input, int fd);
void					validate_room(t_lem_in *lem_in, t_room *room);
void					bfs(t_lem_in *lem_in);
void					free_lem_in(t_lem_in *lem_in);
void					check_links(t_lem_in *lem_in);
void					free_input(t_line *input);
void					ft_strsplit_free(char ***strsplit);
void					print_input(t_line *input, int n);
int						sum_ascii(char *room_name);
void					print_ht_rooms(t_hashtable *ht_rooms);
void					findLinkDirection(t_hashtable *ht_rooms);
void                    ImputCleaning(t_lem_in *lem_in);
t_node					*FindRoomLinks(char *current_room_name, t_hashtable *ht_rooms);

void					print_paths(t_path **paths, int path_num);
int						create_paths(t_lem_in *lem_in);
void					flow(t_lem_in *lem_in, int i, int j);
void					free_paths(t_path **pa, int path_num);
void					free_queue(t_queue *q);
char					*dequeue(t_queue *q);
int						is_empty(t_queue *q);
void					enqueue(t_queue *q, t_room *room, int room_num);
t_queue					*create_queue(int room_num);
t_room					*FindRoomInHashtable(char *room_name, t_hashtable *ht_rooms);
void					print_ht_roomsWithDirection(t_hashtable *ht_rooms);
int						push_old_ants(t_lem_in *lem_in, int supermax, int flows, int ant_index);
void					print_paths_with_ants(t_path *curr, int i);
void					push_ants_along(t_path *pa, t_lem_in *lem_in, int i);
int						index_manager(t_lem_in *lem_in, int maxf, int ant_index);
int						is_short_circuit(t_lem_in *lem_in);
int						len_nei(t_node *n);
void					delete_current_path(t_path *path);
int						check_flow_type(int maxpath, t_lem_in *lem_in);

# define ERR_ANTS_NUM_PARSING	"ERROR: Number of ants is incorrent"
# define ERR_ROOM_PARSING		"ERROR: Can\'t parse room"
# define ERR_ROOM_INIT			"ERROR: Can\'t initialize room"
# define ERR_LINE_INIT			"ERROR: Can\'t initialize line"
# define ERR_READING			"ERROR: Reading error"
# define ERR_ROOM_NAME_DUP		"ERROR: Input has room name duplicate"
# define ERR_ROOM_COORDS_DUP	"ERROR: Input has room coordinates duplicate"
# define ERR_LINK_INIT			"ERROR: Can\'t initialize link"
# define ERR_LINK_PARSING		"ERROR: Can\'t parse link"
# define ERR_LINK_DUP			"ERROR: Input has link duplicate"
# define ERR_NO_LINKS			"ERROR: Input has no links"
# define ERR_START_END_ROOM		"ERROR: Input has no start or end room"
# define ERR_NO_PATH			"ERROR: Input has no path from start to end"

# define ERR_QUEUE_INIT			"ERROR: Can\'t initialize queue"
# define ERR_ALLOCATION         "ERROR: the memory is not allocated"
# define ERR_NO_PATH			"ERROR: Input has no path from start to end"
# define ERR_PATH_INIT			"ERROR: Can\t init path"
# define ERR_MAP				"ERROR"


# define ROOM 2
# define COMMAND 3
# define TABLE_SIZE 100
# define VISITED 1
# define UNVISITED 0
# define UNDIFINED 1
# define DIFINED_DIRECTION 0


#endif
