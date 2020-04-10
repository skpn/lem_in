/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:01:47 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/10 09:59:17 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "unistd.h"
# include "libft.h"

# define CONTINUE 1
# define ACCEPT_START_END 2
# define REJECT_START_END 3
# define START 4
# define END 5

# define PARENT 1
# define BROTHER 2
# define CHILD 3

# define EACH 0
# define DIFF 1
# define SUP 2
# define INF 3
# define INF_EQUAL 4
# define SUP_EQUAL 5
# define NB_ALGO_LAUNCHS 16

# define LIVES_UPPER_LIMIT 1000
# define LIVES_LOWER_LIMIT 1000

# define DEBUG 1

# define PARSING_ERROR -2

# define POS ft_printf("%s - %d\n", __FILE__, __LINE__)

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
	t_path			*path;
	t_lst			*current_room;
}					t_ant;

typedef struct		s_room
{
	unsigned		dist;
	unsigned		has_lvl;
	unsigned		walk;
	char			*name;
	t_path			*previous_path;
	t_path			*active_path;
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
	unsigned		nb_tubes;
	unsigned		shortest;
	unsigned		max_dist;
	unsigned		turns;
	unsigned		max_lives;
	unsigned		lives;
	unsigned		pos;
	unsigned		anthill_size;
	unsigned		algo_flip;
	unsigned		reset_flip;
	unsigned		generic_path_size;
	char			*anthill;
	char			*copy;
	t_room			*start;
	t_room			*end;
	t_h_table		*table;
	t_head			*paths;
	t_config		*final_config;
	t_config		*best_config;
	t_config		*current_config;
	t_path			*generic_path;
	t_lst			*generic_room_lst;
	t_display		*display;
}					t_lem;

t_config			*alloc_new_config(void);
t_display			*alloc_new_display(unsigned total_rooms);
t_lvl				*alloc_new_lvl(void);
t_path				*alloc_new_path(void);
t_room				*alloc_new_room(char *name);

void				balance_load(t_lem *lem);
int					best_to_final(t_lem *lem);

t_path				*copy_generic_path(t_lem *lem);

int					display_lem(t_lem *lem);

int					exit_lem(t_lem *lem, int ret);

void				free_config(t_config **config);
void				free_lvl(t_lvl **lvl);
void				free_path(t_path **path);
void				free_paths(t_head **path);
void				free_table_room(t_h_elem *room_h_elem);

int					get_anthill(t_lem *lem);
int					get_rooms(t_lem *lem, char *anthill_copy);
int					get_tubes(t_lem *lem, char *anthill_copy);

int					init_lem(t_lem *lem);

void				kill_dead_rooms(t_lem *lem, t_room *dead_room);
void				kill_end_children(t_room *end, unsigned max_dist);

int					manage_com(t_lem *lem, char *anthill, int *opt);
int					manage_valid_path(t_lem *lem);

int					parse_input(t_lem *lem);
void				print_anthill(char *lem);
void				print_ants_tab(t_ant **tab);
void				print_config(t_config *config);
void				print_display(t_display *display);
void				print_lem(t_lem *lem);
void				print_lvl(t_lvl *lvl);
void				print_path(t_path *path);
void				print_paths(t_head *path_head);
int					print_room_elem(t_h_elem *room_elem);
void				print_room(t_room *room);

int					seek_paths(t_lem *lem);
t_display			*set_display(t_lem *lem);
int					set_graph(t_lem *lem);
void				set_next_lvl_dists(t_lvl *lvl);
void				set_next_lvl_families(t_lvl *lvl, t_room *end);
void				start_joined_to_end(t_lem *lem);

int					try_path(t_lem *lem);

int					update_best_config(t_lem *lem);


#endif
