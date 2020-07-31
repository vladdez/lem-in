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

typedef struct			s_path
{
	int					len;
	int					ant_index;
	int					head;
	char				*name;
	struct s_path		*next;
}						t_path;

typedef struct			s_line
{
	char				*data;
	struct s_line		*next;
}						t_line;

typedef struct			s_nei   // связный список для соседей
{
	int					b; 
    char				*to;  //  куда
    struct s_nei		*next;  // узлы одного уровня
}						t_nei;


typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					type;
	int					bfs_level;
	int					visited;
	/*int					ant_number;*/
	t_nei				*input_nei;
	t_nei				*output_nei;
	struct s_room		*next;
}						t_room;

typedef struct			s_link
{
	t_room				*start;
	t_room				*end;
	struct s_link		*next;
	struct s_link		*prev;
}						t_link;

typedef struct			s_lem_in
{
	int					ants_start;
	int					ants_end;
	int					ant_num;
	int                 room_num;
	int					path_num;
	t_room				*rooms;
	t_room				*start;
	t_room				*end;
	t_room              **hash_table;
	t_link				*links;
	int					bfs_length;
	t_path				**paths;
	/*t_location			*locations;
	t_turn				*turns;
	t_ant				*ants;*/
}						t_lem_in;

typedef struct			s_queue
{
	char				*name;
	struct s_queue		*next;
}						t_queue;



int						main(int ac, char **av);
void					*terminate(char *er);

void					parse_ants(t_lem_in *lem_in, int fd);
void					parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp);
void					parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp);



int						is_room(char *str);
int						is_comment(char *str);
int						ft_isint(char *tmp);
int						is_command(char *str);


t_line					*read_line(t_line **input, int fd);
void					validate_room(t_room *room);
void					validate_link(t_lem_in *lem_in, t_link *link);
void					bfs(t_lem_in *lem_in);
void					free_lem_in(t_lem_in **lem_in);
void					check_links(t_lem_in *lem_in);
void					free_input(t_line **input);	
void					ft_strsplit_free(char ***strsplit);
void					print_input(t_line *input, int n);
int						iswhat(char *str);
void					create_hash_table(t_lem_in *lem_in);
int						hash_fun(char *room_name);
int						hash_fun_room(char *str);
void					free_nei(t_nei **sentenced);
t_room					*find_room(t_room *room, char *name);
void					align_links(t_lem_in *lem_in);
int						create_paths(t_lem_in *lem_in);
void					flow(t_lem_in *lem_in, int i, int j);

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

# define ERR_NO_ROOM			"ERROR: No such room given"
# define ERR_QUEUE_INIT			"ERROR: Can\'t initialize queue"
# define ERR_DASH_NAME			"ERROR: We do not parse names with dashes"
# define ERR_ALLOCATION			"ERROR: Memory allocation error"
# define ERR_PATH_INIT			"ERROR: Can\t init path"

# define TABLEN 100	
#endif
