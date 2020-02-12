#include "lem-in.h"

int 		get_path_length(t_graph **graph, int count_rooms, int next_room)
{
	int		length;

	length = 1;
	while (graph[next_room][0].bfs_lvl != MAX_INT)
	{
		length++;
		next_room = find_first_output(graph, count_rooms, next_room);
	}
	return (length);
}

int			*get_path_rooms(t_graph **graph, int count_rooms, int next_room, int length)
{
	int		*rooms;
	int		i;

	i = 0;
	if (!(rooms = (int*)malloc(sizeof(int) * length)))
		exit(-1);
	while (i < length - 1)
	{
		rooms[i] = next_room;
		next_room = find_first_output(graph, count_rooms, next_room);
		i++;
	}
	return (rooms);
}

int			get_first_room(t_graph **graph, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[i][0].bfs_lvl == 0)
			return (i);
		i++;
	}
}