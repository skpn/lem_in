/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:01:47 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/11 14:17:00 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define LEM_BUFF 500000
# define MAX_SIZE 1500000
# define ACCEPT_START_END 1
# define REJECT_START_END 2
# define START 3
# define END 4
# define MALLOC_ERROR -1
# define PARSING_ERROR -2
# define PARENT 1
# define BROTHER 2
# define CHILD 3

# define EACH 0u
# define DIFF 1u
# define SUP 2u
# define INF 3u
# define INF_EQUAL 4u
# define SUP_EQUAL 5u
# define NB_ALGO_LAUNCHS 18u

# define LIVES_UPPER_LIMIT 500
# define LIVES_LOWER_LIMIT 500
# define DEBUG 1

typedef struct		s_path
{
	unsigned		load;
	unsigned		is_dead;
	t_head			*rooms;
}					t_path;

typedef struct		s_ant
{
	unsigned		id;
	unsigned		wait;
	unsigned		max;
	t_path			*path;
	t_lst			*current_room;
}					t_ant;

typedef struct		s_room
{
	unsigned		dist;
	unsigned		has_lvl;
	unsigned		walk;
	unsigned		walk_2;
	char			*name;
	t_path			*previous_path;
	t_path			*current_path;
	t_head			*parents;
	t_head			*children;
}					t_room;

typedef struct		s_lvl
{
	unsigned		dist;
	t_head			*rooms;
}					t_lvl;

typedef struct		s_config
{
	unsigned		turns;
	t_head			*paths;
}					t_config;

typedef struct		s_display
{
	unsigned		last_id;
	unsigned		turn;
	unsigned		lem_turns;
	unsigned		first_print;
	unsigned		total_rooms;
	size_t			nb_ants;
	t_config		*best;
	t_ant			**ants_tab;
}					t_display;

typedef struct		s_lem
{
	unsigned		nb_ants;
	unsigned		nb_rooms;
	unsigned		max_paths;
	unsigned		most_paths;
	unsigned		shortest;
	unsigned		max_dist;
	unsigned		turns;
	unsigned		nb_tubes;
	unsigned		max_lives;
	unsigned		lives;
	unsigned		anthill_size;
	unsigned		scramble_flip;
	unsigned		pos;
	unsigned		algo_flip;
	unsigned		reset_flip;
	char			*anthill;
	char			*copy;
	t_room			*start;
	t_room			*end;
	t_h_table		*table;
	t_head			*paths;
	t_config		*final_config;
	t_config		*best_config;
	t_config		*current_config;
	t_display		*display;
}					t_lem;

int					get_anthill(t_lem *lem);
int					get_rooms(t_lem *lem, char *anthill_copy);
int					get_tubes(t_lem *lem, char *anthill_copy);
int					manage_com(t_lem *lem, char *anthill, int *opt);
int					set_graph(t_lem *lem);
t_lem				*alloc_new_lem(void);
t_room				*alloc_new_room(void);
t_config			*alloc_new_config(void);
t_path				*alloc_new_path(void);
t_lvl				*alloc_new_lvl(void);
t_display			*alloc_new_display(unsigned total_rooms);
int					parse_input(t_lem *lem);
void				set_next_lvl_dists(t_lvl *lvl);
void				set_next_lvl_families(t_lvl *lvl, t_room *end);
void				kill_dead_rooms(t_lem *lem, t_room *dead_room);
void				kill_end_children(t_room *end, unsigned max_dist);
int					seek_paths(t_lem *lem);
int					manage_valid_path(t_lem *lem, t_path *path);
int					update_best_config(t_lem *lem);
void				balance_load(t_lem *lem);
void				start_joined_to_end(t_lem *lem);
t_display			*set_display(t_lem *lem);
int					display_lem(t_lem *lem);
int					exit_lem(t_lem **lem, char *msg, int ret);
void				free_table_room(void **room);
void				free_config(t_config **config);
void				free_path(t_path **path);
void				free_paths(t_head **path);
void				free_lvl(t_lvl **lvl);
void				print_anthill(char *lem);
void				print_lem(t_lem *lem, char *args);
int					print_room_elem(t_h_elem *room_elem);
void				print_room(t_room *room);
void				print_config(t_config *config);
void				print_path(t_path *path);
void				print_paths(t_head *path_head);
void				print_lvl(t_lvl *lvl);
void				print_ants_tab(t_ant **tab);
void				print_display(t_display *display);

#endif
