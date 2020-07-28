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

typedef struct			s_node   // связыный список для соседей
{
    char				*node;  //
    struct s_node	*next;  // узлы одного уровня
}						t_node;

typedef struct			s_room
{
	char				*name;
	int                 visit;      // 0 no 1 yes
	int					bfs_level;
	t_node              *link;
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
    char                *name;
    int					x;
    int					y;
    struct s_coordinate *next;
}                       t_coordinate;


typedef struct			s_lem_in
{
	int					ant_num;
	int                 room_num;
	t_room				*start;
	t_room				*end;
	t_coordinate        *coordinate;
	t_hashtable         *hash_table;
	int					bfs_length;
	/*t_path				*paths;
	t_location			*locations;
	t_turn				*turns;
	t_ant				*ants;*/
}						t_lem_in;

typedef struct			s_queue
{
	char				**room;
	int                 toward;
	int       		    from;
}						t_queue;


int						main(int ac, char **av);
void					*terminate(char *er);

void		parse_ants(t_lem_in *lem_in, int fd);
void		parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp);
void		parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp);
t_node      *neighbour_init();
t_coordinate *coordinate_create();

int						is_room(char *str);
int						is_comment(char *str);
int						ft_isint(char *tmp);
int						is_command(char *str);


t_line					*read_line(t_line **input, int fd);
void					validate_room(t_lem_in *lem_in, t_room *room);
void					bfs(t_lem_in *lem_in);
void					free_lem_in(t_lem_in *lem_in);
void					check_links(t_lem_in *lem_in);
void					free_input(t_line *input);
void					ft_strsplit_free(char ***strsplit);
void					print_input(t_line *input, int n);
int sum_ascii(char *room_name);
void print_hash_table(t_hashtable *hash_table);

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
# define ROOM 2
# define COMMAND 3
# define TABLE_SIZE 10



#endif
