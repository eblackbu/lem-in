#include "lem-in.h"

int			get_len_suur(t_room *rooms, int count_rooms, int last_room, int end_room)
{
	int		len;

	len = 1;
	while (rooms[last_room].bfs_lvl != 0)
	{
		last_room = rooms[last_room].prev->number;
		len++;
	}
	return (len);
}

t_ant		*get_roomnumpath_suur(t_room *rooms, int count_rooms, int last_room, int len)
{
	t_ant	*roompath;
	int		i;

	if (!(roompath = (t_ant*)malloc(sizeof(t_ant) * len)))
		exit(-1);
	i = len - 1;
	while (i >= 0)
	{
		if (i == len - 1)
			roompath[i].roomnum = get_end_room(rooms, count_rooms);
		else
		{
			roompath[i].roomnum = last_room;
			if (i > 0)
				last_room = rooms[last_room].prev->number;
		}
		roompath[i].is_ant_here = 0;
		i--;
	}
	return (roompath);
}
