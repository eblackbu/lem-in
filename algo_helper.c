#include "lem-in.h"

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

