#include "lem-in.h"

t_path		*set_path(t_graph **graph, int count_rooms, int next_room)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		exit(-1);
	path->length = get_path_length(graph, count_rooms, next_room);
	path->roomnum_path = get_path_rooms(graph, count_rooms, next_room, path->length);//TODO
	return (path);
}

t_path		**get_paths(t_graph **graph, int count_rooms)
{
	t_path	**paths;
	int		first_room;
	int		i;
	int		j;

	first_room = get_first_room(graph, count_rooms);
	if (!(paths = (t_path**)malloc(sizeof(t_path*) * count_output_links(graph, count_rooms, first_room))))
		exit(-1);
	i = 0;
	j = 0;
	while (i < count_rooms)
	{
		if (graph[first_room][i].link == -1)
		{
			paths[j] = set_path(graph, count_rooms, i);
			j++;
		}
		i++;
	}
	print_paths(paths, count_output_links(graph, count_rooms, first_room));
	return (paths);
}