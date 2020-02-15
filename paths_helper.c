#include "lem-in.h"

int 		get_path_length(t_graph **graph, int count_rooms, int next_room)
{
	int		length;
	int 	tmp_room;

	length = 1;
	while (graph[next_room][0].bfs_lvl != MAX_INT)
	{
		length++;
		tmp_room = next_room;
		next_room = find_first_output(graph, count_rooms, next_room);
		if (graph[next_room][tmp_room].link == 1 && graph[tmp_room][next_room].link == 1)
			graph[tmp_room][next_room].link = -1;
	}
	return (length);
}

t_ant		*get_path_rooms(t_graph **graph, int count_rooms, int next_room, int length)
{
	t_ant	*rooms;
	int 	tmp_room;
	int		i;

	i = 0;
	if (!(rooms = (t_ant*)malloc(sizeof(t_ant) * length)))
		exit(-1);
	while (i < length)
	{
		rooms[i].roomnum = next_room;
		rooms[i].is_ant_here = 0;
		if (graph[next_room]->bfs_lvl == MAX_INT)
			break ;
		tmp_room = next_room;
		next_room = find_first_output(graph, count_rooms, next_room);
		if (graph[next_room][tmp_room].link == 1 && graph[tmp_room][next_room].link == 1)
			graph[tmp_room][next_room].link = -1;
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

int			get_last_room(t_graph **graph, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[i][0].bfs_lvl == MAX_INT)
			return (i);
		i++;
	}
}