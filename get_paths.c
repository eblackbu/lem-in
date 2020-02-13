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

t_path		**sort_paths(t_path **paths, int count_paths)//TODO изменить на нормальную сортировку
{
	t_path	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < count_paths - 1)
	{
		if (paths[i]->length > paths[i + 1]->length)
		{
			tmp = paths[i];
			paths[i] = paths[i + 1];
			paths[i + 1] = tmp;
			flag++;
		}
		i++;
		if (i == count_paths - 1 && flag)
		{
			i = 0;
			flag = 0;
		}
	}
	return (paths);
}

t_path		**get_paths(t_graph **graph, int count_rooms)
{
	t_path	**paths;
	int		first_room;
	int		i;
	int		j;
	int 	count_paths;

	first_room = get_first_room(graph, count_rooms);
	count_paths = count_output_links(graph, count_rooms, first_room);
	if (!(paths = (t_path**)malloc(sizeof(t_path*) * count_paths)))
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
	return (sort_paths(paths, count_paths));
}