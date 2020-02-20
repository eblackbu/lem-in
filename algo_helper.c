#include "lem-in.h"

int		get_start_room(t_room *rooms, int count_rooms)
{
	int		start;

	start = 0;
	while (rooms[start].bfs_lvl != 0 && start != count_rooms)
		start++;
	if (start == count_rooms)
		exit(-1);
	return (start);
}

int		get_end_room(t_room *rooms, int count_rooms)
{
	int		end;

	end = 0;
	while (rooms[end].bfs_lvl != MAX_INT && end != count_rooms)
		end++;
	if (end == count_rooms)
		exit(-1);
	return (end);
}

int 		switch_links(t_path *path, t_room *rooms, int count_rooms)
{
	int 	i;
	int 	first;

	i = 0;
	first = get_start_room(rooms, count_rooms);
	while (i < path->length)
	{
		if (i == 0)
			rooms = set_neg_weight(rooms, path->roomnum_path[i].roomnum, first);
		else
			rooms = set_neg_weight(rooms, path->roomnum_path[i].roomnum, path->roomnum_path[i - 1].roomnum);
		//print_links(rooms, count_rooms);
		i++;
	}
	return (1);
}

t_room		*set_null_distance(t_room *rooms, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		if (rooms[i].bfs_lvl != 0)
			rooms[i].dist = MAX_INT;
		i++;
	}
	return (rooms);
}

