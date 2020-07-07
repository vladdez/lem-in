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



typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					type;
	int					bfs_level;
	/*int					input_links;
	int					output_links;
	int					ant_number;*/
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
	t_room				*rooms;
	t_room				*start;
	t_room				*end;
	t_link				*links;
	int					bfs_length;
	/*t_path				*paths;
	t_location			*locations;
	t_turn				*turns;
	t_ant				*ants;*/
}						t_lem_in;

typedef struct			s_queue
{
	t_room				*room;
	struct s_queue		*next;
}						t_queue;


int						main(int ac, char **av);
void    				*terminate(char *er);

void					parse_ants(t_lem_in **lem_in, int fd);
void					parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **line);
void					parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **line);



int						is_room(char *str);
int						is_comment(char *str);
int						ft_isint(char *tmp);
int						is_command(char *str);


t_line  				*read_line(t_line **input, int fd);
void		  			validate_room(t_lem_in *lem_in, t_room *room);
void		  			validate_link(t_lem_in *lem_in, t_link *link);
void					bfs(t_lem_in *lem_in);
void					free_lem_in(t_lem_in **lem_in);




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



#endif
