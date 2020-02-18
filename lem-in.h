#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START_ROOM 1
# define END_ROOM 2
# define MAX_INT 2147483647

typedef struct	s_edge
{
	int 		weight;
	int 		link;
}				t_edge;

typedef struct		s_room
{
	int				number;
	char			*name;
	int				x;
	int				y;
	int				dist;
	int				bfs_lvl;
	int				in_use;
	t_edge			*edges;
	struct s_room	*parent;
	struct s_room	*prev;
	struct s_room	*next;
}					t_room;

typedef struct			s_roomlist
{
	t_room				*room;
	struct s_roomlist	*next;
}						t_roomlist;


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
	//struct s_path		*next;
}						t_path;

typedef struct 			s_lemin
{
	long long			count_ants; //TODO выяснить, какое максимальное значение муравьев
	t_roomlist			*list;
	t_room				*rooms;
	t_path				*paths;
}						t_lemin;

/*
** algo_helper.c
*/
int						get_end_room(t_room *rooms, int count_rooms);
int						switch_links(t_path *path, t_room *rooms, int count_rooms);
t_room					*set_null_distance(t_room *rooms, int count_rooms);

/*
** bellman-ford.c
*/
t_path					*get_new_paths(t_room *rooms, int count_rooms, int count_paths);

/*
** suurballe_helper.c
*/
int						get_len_suur(t_room *rooms, int count_rooms, int last_room, int end_room);
t_ant					*get_roomnumpath_suur(t_room *rooms, int count_rooms, int last_room, int len);

/*
** suurballe.c
*/
t_path					*del_overused_edges(t_room *rooms, int count_rooms, int count_paths);
void get_another_paths(t_lemin **lemin, int count_rooms);

/*
** initialize_room.c
*/
char					*get_name(char *roomline);
int						get_coordinate_x(char *roomline);
int						get_coordinate_y(char *roomline);
t_room					*init_room(int num, char *roomline, int start_end);

/*
** roomlist_helper.c
*/
int						check_nameplace(t_roomlist **map, char *name, int x, int y);
void					free_all_rooms(t_roomlist **map);
void					add_new_room(t_roomlist **map, char *line, int start_end);

/*
** rooms_checker.c
*/
int						is_number(char *line);
int 					count_spaces(char *roomline);
int						check_roomline(char *roomline);
int						get_start_end(char *line);
char					*get_rooms(t_roomlist **list);

/*
** links_checker.c
*/
t_room					*set_info_links(t_room *links, t_roomlist *list, int count_rooms);
t_room					*init_links(int count_rooms, t_roomlist *list);
int						set_link(int i, int j, t_room *map);
int						check_link(t_lemin **lemin, char *linkline, int count_rooms);

/*
** dinic_algo.c
*/
int						add_children_layers(t_room **rooms, int count_rooms, int roomnum);
t_path					*get_first_path(t_lemin *lemin, int count_rooms, int layer);

/*
** map_checker.c
*/
void					print_links(t_room *rooms, int count_rooms);
int						get_count_rooms(t_roomlist *roomlist);
void					get_links(t_lemin **lemin, char *linkline);
void					check_map(t_lemin **lemin);

/*
** validation.c
*/
long long				check_ants(void);
t_lemin					*validation(void);

/*
** free_all.c
*/
void					del_roomlist(t_roomlist **map);
void					del_all_rooms(t_room **rooms, int count_rooms);
void					del_all_paths(t_path **paths, int count_paths);
void					free_all(t_lemin *lemin, int count_rooms, int count_paths);

void 			print_paths(t_path *paths, t_room *rooms, int count_paths);

#endif