#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START_ROOM 1
# define END_ROOM 2
# define MAX_INT 2147483647

typedef struct	s_room
{
	int			number;
	char		*name;
	int			x;
	int			y;
	int			bfs_level;
}				t_room;

typedef struct			s_roomlist //возможно совместить с s_room
{
	t_room				*room;
	struct s_roomlist	*next;
}						t_roomlist;

typedef struct			s_graph
{
	char 				*name;
	int					link;
	int					bfs_lvl;
}						t_graph;

typedef struct			s_ant
{
	int					is_ant_here;
	int					roomnum;
	long long			antnum;
}						t_ant;

typedef struct			s_path
{
	int					length;
	t_ant				*roomnum_path;
}						t_path;

typedef struct 			s_lemin
{
	long long			count_ants; //сделать atoll потом
	t_roomlist			*map;
	t_graph 			**links;
	t_path				**paths;
}						t_lemin;

//initialize_room.c
char					*get_name(char *roomline);
int						get_coordinate_x(char *roomline);
int						get_coordinate_y(char *roomline);
t_room					*init_room(int num, char *roomline, int start_end);

//roomlist_helper.c
int						check_nameplace(t_roomlist **map, char *name, int x, int y);
void					free_all_rooms(t_roomlist **map);
void					add_new_room(t_roomlist **map, char *line, int start_end);

//rooms_checker.c
int						is_number(char *line);
int 					count_spaces(char *roomline);
int						check_roomline(char *roomline);
int						get_start_end(char *line);
char					*get_rooms(t_roomlist **map);

//links_checker.c
t_graph					**set_info_links(t_graph **links, t_roomlist *map, int count_rooms);
t_graph					**init_links(int count_rooms, t_roomlist *map);
int						set_links(int i, int j, t_graph **graph);
int						check_links(t_lemin **lemin, char *linkline, int count_rooms);

//bfs_helper.c
int						add_children_layers(t_graph ***graph, int count_rooms, int roomnum);
t_graph					**set_bfs_levels(t_graph **graph, int count_rooms, int layer);

//map_checker.c
void					print_links(t_graph **graph, int count_rooms);
int						get_count_rooms(t_roomlist *roomlist);
void					get_links(t_lemin **lemin, char *linkline);
void					check_map(t_lemin **lemin);

//validation.c
long long				check_ants(void);
t_lemin					*validation(void);

//algo_helper.c
int						get_max_layer(t_graph **graph, int count_rooms);
int 					find_first_input(t_graph **graph, int count_rooms, int roomnum);
int						find_first_output(t_graph **graph, int count_rooms, int roomnum);
int						count_input_links(t_graph **graph, int count_rooms, int i);
int						count_output_links(t_graph **graph, int count_rooms, int i);

int						check_all_forks(t_graph **graph, int count_rooms);

//algorithm.c
t_graph					**del_all_links(t_graph **graph, int count_rooms, int i);
t_graph					**del_samelayer_links(t_graph **graph, int count_rooms, int i);
t_graph					**del_unused_links(t_graph **graph, int count_rooms);
t_graph					**del_dead_ends(t_graph **graph, int count_rooms);
t_path					**get_solution(t_graph **graph, int count_rooms);

//input_forks.c
int						is_nice_way(t_graph **graph, int count_rooms, int roomnum);
t_graph					**del_input_fork(t_graph **graph, int count_rooms, int roomnum, int needed_input);
t_graph					**check_input(t_graph **graph, int count_rooms, int i);
t_graph					**find_input_forks(t_graph **graph, int count_rooms);

//output_forks.c
t_graph					**find_output_forks(t_graph **graph, int count_rooms);

//paths_helper.c
int						get_first_room(t_graph **graph, int count_rooms);
int						get_last_room(t_graph **graph, int count_rooms);
int						get_path_length(t_graph **graph, int count_rooms, int next_room);
t_ant					*get_path_rooms(t_graph **graph, int count_rooms, int next_room, int length);

//get_paths.c
t_path					**get_paths(t_graph **graph, int count_rooms);

//print_helper.c
void					print_solution(t_lemin *lemin, long long count_ants);

//main.c
void					print_paths(t_graph **graph, t_path **paths, int count_paths);

/*
** free_all.c
*/
void					free_all(t_lemin *lemin, int count_rooms, int count_paths);
#endif