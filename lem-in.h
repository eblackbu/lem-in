
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
	int			*input_ways;
	int			*output_ways;
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

typedef struct 			s_lemin
{
	long long			count_ants; //сделать atoll потом
	t_roomlist			*map;
	t_graph 			**links;
}						t_lemin;

//initialize_room.c
char					*get_name(char *roomline);
int						get_coordinate_x(char *roomline);
int						get_coordinate_y(char *roomline);
t_room					*init_room(int num, char *roomline, int start_end);

//roomlist_helper.c
int						check_nameplace(t_roomlist **map, char *name, int x, int y);
void					del_all_rooms(t_roomlist **map);
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

//map_checker.c
int						get_count_rooms(t_roomlist *roomlist);
void					get_links(t_lemin **lemin, char *linkline);
void					check_map(t_lemin **lemin);

//validation.c
long long				check_ants(void);
t_lemin * validation(void);

#endif
