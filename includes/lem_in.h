/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:01:47 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 22:25:03 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include "libft.h"
# define PARENT 1
# define BROTHER 2
# define CHILD 3
# define ADD_PATH 0
# define ADD_PATH 0
# define ADD_PATH 0
void	*g_ptr;
typedef struct		s_path
{
	unsigned		load;
	unsigned		len;
	t_head			*rooms;
}					t_path;

typedef struct		s_room
{
	unsigned		dist;
	unsigned		has_lvl;
	unsigned		walk;
	char			*name;
	t_path			*current_path;
	t_head			*parents;
	t_head			*children;
}					t_room;

typedef struct		s_lvl
{
	unsigned		dist;
	t_head			*rooms;
}					t_lvl;

<<<<<<< HEAD
typedef struct		s_path
{
	unsigned		turns;
	unsigned		walk_limit;
	t_head			*rooms;
}					t_path;

typedef struct		s_config
{
	unsigned		turns;
=======
typedef struct		s_config
{
	unsigned		turns;
	unsigned		nb_paths;
>>>>>>> 96f7d4e307ecb34585e26d44e0e5cfae627b55ba
	t_head			*paths;
}					t_config;

typedef struct 		s_lem
{
	size_t			nb_ants;
	unsigned		nb_rooms;
	unsigned		max_paths;
	unsigned		shortest;
	unsigned		max_dist;
	char			*anthill;
	t_head			*rooms;
	t_room			*start;
	t_room			*end;
	t_head			*config_lst;
}					t_lem;

int					gnl_lem_in(int fd, unsigned *pos, unsigned *done
	, char **line);
char				*ft_strjoin_anthill(char **s1, char **s2, int opt);
int					parse_ants(t_lem *lem, char **line, int *index);
int					parse_room(t_lem *lem, char **line, int *index);
int					parse_tube(t_lem *lem, char **line, int *index);

int					set_graph(t_lem *lem);
int					init_lem(t_lem **lem);
t_room				*alloc_new_room(void);
void				free_room(t_head *rooms, t_room **room);
t_config			*alloc_new_config(void);
void				free_config(t_config **config);
t_path				*alloc_new_path(void);
void				free_path(t_path **path);
int					exit_lem(t_lem *lem, char *msg, int ret);
int					parse_input(t_lem *lem);
void				set_next_lvl_dists(t_lvl *lvl);
void				set_next_lvl_families(t_lvl *lvl, t_room *end);
<<<<<<< HEAD
void				kill_dead_rooms(t_lem *lem, t_room *dead_room);
=======
void				get_next_lvl_rooms(t_lvl *lvl);
int					seek_paths(t_lem *lem);
int					update_config(t_lem *lem, t_config *config
	, t_path *new_path);

>>>>>>> 96f7d4e307ecb34585e26d44e0e5cfae627b55ba

void				print_anthill(char *lem);
void				print_lem(t_lem *lem, char *args);
void				print_room(t_room *room);
void				print_rooms(t_head *rooms);
//void				print_room(t_room *room, char *args, int opt);
//void				print_rooms(t_head *rooms, char *args, int opt);
//void				print_rooms_addr(t_head *rooms);
void				print_lvl(t_lvl *lvl);
#endif