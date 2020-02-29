/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:52:50 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 14:25:29 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START_ROOM 1
# define END_ROOM 2
# define MAX_INT 2147483647

typedef struct			s_link
{
	int					weight;
	int					roomnum;
	struct s_link		*next;
}						t_link;

typedef struct			s_room
{
	int					number;
	char				*name;
	int					x;
	int					y;
	int					dist;
	int					bfs_lvl;
	int					in_use;
	t_link				*links;
	struct s_room		*prev;
	struct s_room		*next;
	struct s_room		*new_prev;
	struct s_room		*new_next;
}						t_room;

typedef struct			s_roomlist
{
	t_room				*room;
	struct s_roomlist	*next;
}						t_roomlist;

typedef struct			s_ant
{
	int					is_ant_here;
	int					roomnum;
	int					antnum;
}						t_ant;

typedef struct			s_path
{
	int					length;
	t_ant				*roomnum_path;
}						t_path;

typedef struct			s_lemin
{
	int					count_ants;
	t_roomlist			*list;
	t_room				*rooms;
	t_path				*paths;
}						t_lemin;

/*
** algo_helper.c
*/
int						get_start_room(t_room *rooms, int count_rooms);
int						get_end_room(t_room *rooms, int count_rooms);
int						switch_links(t_path *path, t_room *rooms, \
									int count_rooms);
t_room					*set_null_distance(t_room *rooms, int count_rooms);

/*
** bellman-ford.c
*/
int						check_ifused_room(t_room *rooms, int room_from, \
											int room_where);
void					set_distance(t_room **rooms, int i, int j, int weight);
int						get_distance(t_room **rooms, int count_rooms);
t_path					*get_new_paths(t_room *rooms, int count_rooms, \
										int count_paths);

/*
** dinic.c
*/
int						add_children_layers(t_room **rooms, int roomnum);
int						get_first_path_length(t_room *rooms, int count_rooms);
t_ant					*get_first_roomnum_path(t_room *rooms, \
												int count_rooms, int len);
t_path					*set_first_path(t_lemin *lemin, int count_rooms);
t_path					*get_first_path(t_lemin *lemin, \
										int count_rooms, int layer);

/*
** free_all.c
*/
void					del_roomlist(t_roomlist **map);
void					del_all_links(t_room room);
void					del_all_rooms(t_room *rooms, int count_rooms);
void					del_all_paths(t_path *paths, int count_paths);
void					free_all(t_lemin *lemin, \
										int count_rooms, int count_paths);

/*
** initialize_room.c
*/
char					*get_name(char *roomline);
int						get_coordinate_x(char *roomline);
int						get_coordinate_y(char *roomline);
t_room					*init_room(int num, char *roomline, int start_end);

/*
** links_checker.c
*/
t_room					*set_info_links(t_room *links, t_roomlist *list, \
										int count_rooms);
t_room					*init_links(int count_rooms, t_roomlist *list);
int						set_link(int i, int j, t_room *map);
int						check_link(t_lemin **lemin, char *link, \
									int count_rooms);

/*
** links_helper.c
*/
int						get_weight_link(t_room *rooms, int room_first, \
										int room_where);
t_room					*del_link(t_room *rooms, int room_first, \
										int room_where);
t_link					*new_link(int weight, int room);
t_link					*add_new_link(t_link *links, int weight, int room);

/*
** map_checker.c
*/
int						get_count_rooms(t_roomlist *roomlist);
int						check_start_end(t_room *rooms, int count_rooms);
void					get_links(t_lemin **lemin, char *linkline);
void					check_map(t_lemin **lemin);

/*
** norme_helper.c
*/

int						calc_first_step(t_lemin **lemin, int path_val, \
										int i, int all_ants);
int						calc_step(t_lemin **lemin, int path_val, int i);

/*
** paths_helper.c
*/
int						is_dupl_path(t_path *paths, int count_paths);
int						is_better_solution(t_path *paths, int count_paths, \
											int count_ants, int *prev_solu);
void					sort_paths(t_path **paths, int count_paths);
void					print_roomname(char *name, int num);
void					print_paths(t_path *paths, t_room *rooms, \
									int count_paths);

/*
** print_map.c
*/
void					print_room(t_room *room);
void					print_links(t_room *rooms, int i);
void					print_map(t_lemin *lemin, int count_rooms);

/*
** print_helper.c
*/
int						is_fast_path(t_path *paths, int count_ants, \
									int path_val);
int						print_ant_move(t_path path, t_room *graph, \
									int room, int *flag_space);
int						make_step(t_lemin *lemin, int count_paths, \
									int all_ants);
int						make_pathstep(t_lemin **lemin, int path_val, \
									int all_ants, int flag_space);
void					print_solution(t_lemin *lemin, int count_ants, \
									int count_paths);

/*
** roomlist_helper.c
*/
int						check_nameplace(t_roomlist **map, char *name, \
									int x, int y);
void					add_new_room(t_roomlist **map, char *line, \
									int start_end);

/*
** rooms_checker.c
*/
int						is_number(char *line);
int						is_second_number(char *line);
int						count_spaces(const char *roomline);
int						check_roomline(char *roomline);
int						get_start_end(char *line);

/*
** suurballe.c
*/
t_path					*set_new_paths(t_room *rooms, int count_rooms, \
										int count_paths, int end_room);
t_room					*set_neg_weight(t_room *rooms, int next_room, \
										int prev_room);
t_path					*del_overused_edges(t_room *rooms, int count_rooms, \
										int count_paths);
void					get_another_paths(t_lemin **lemin, int count_rooms, \
										int *count_paths);

/*
** suurballe_helper.c
*/
int						get_len_suur(t_room *rooms, int last_room);
t_ant					*get_roomnumpath_suur(t_room *rooms, int count_rooms, \
										int last_room, int len);

/*
** validation.c
*/
int check_ants(void);
char					*get_rooms(t_roomlist **list);
t_lemin					*validation(void);

/*
** main.c
*/
void					error_exit(void);

#endif
