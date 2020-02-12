#include "lem-in.h"

int			make_pathstep(t_lemin **lemin, int path_val)
{
	int		i;

	i = (*lemin)->paths[path_val]->length - 2;
	//while (i >= 0)
	//{
	//	if ()
	//}
}

int			make_step(t_lemin *lemin, int count_paths, int flag)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (i < count_paths)
	{
		tmp += make_pathstep(&lemin, i++);
	}
	return (tmp);
}

void		print_solution(t_lemin *lemin)
{
	int 	first_room;
	int		last_room;
	int		count_rooms;
	int		flag;
	int		count_paths;

	count_rooms = get_count_rooms(lemin->map);
	first_room = get_first_room(lemin->links, count_rooms);
	last_room = get_last_room(lemin->links, count_rooms);
	count_paths = count_output_links(lemin->links, count_rooms, first_room);
	flag = 1;
	while (flag)
	{
		flag = make_step(lemin, count_paths, flag);
	}
}

