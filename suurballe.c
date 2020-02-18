#include "lem-in.h"
//TODO Беллман-Форд. Пройтись по всем комнатам, в каждой комнате смотреть каждую связь.
// Если связь есть, смотреть в переменную distance и обновлять, если distance больше чем путь до пред вершины + 1

int				get_last_room(t_room *rooms, int count_rooms, int end)
{
	int			i;

	i = 0;
	while (i < count_rooms)
	{
		if (rooms[end].edges[i].link && rooms[i].edges[end].link && rooms[i].dist == rooms[end].dist - 1)
			return (i);
		i++;
	}
	exit(-1);
}

t_path			*set_new_paths(t_room *rooms, int count_rooms, int count_paths, int end_room)
{
	t_path		*paths;
	int			i;
	int			j;

	i = 0;
	if (!(paths = (t_path*)malloc(sizeof(t_path) * (count_paths + 1))))
		exit(-1);
	j = 0;
	while (j < count_rooms)
	{
		if (rooms[end_room].edges[j].link && rooms[end_room].edges[j].weight == -1)
		{
			paths[i].length = get_len_suur(rooms, count_rooms, j, end_room);
			paths[i].roomnum_path = get_roomnumpath_suur(rooms, count_rooms, j, paths[i].length);
			i++;
		}
		j++;
	}
	return (paths);
}

t_path 			*del_overused_edges(t_room *rooms, int count_rooms, int count_paths)
{
	int			end_room;
	int			tmp_room;
	int 		last_room;

	end_room = get_end_room(rooms, count_rooms);
	last_room = get_last_room(rooms, count_rooms, end_room);
	rooms[last_room].edges[end_room].link = 0;
	rooms[last_room].edges[end_room].weight = 0;
	rooms[end_room].edges[last_room].weight = -1;
	while (rooms[last_room].bfs_lvl != 0)
	{
		tmp_room = last_room;
		last_room = rooms[tmp_room].prev->number;
		rooms[last_room].edges[tmp_room].link = 0;
		rooms[last_room].edges[tmp_room].weight = 0;
		rooms[tmp_room].edges[last_room].weight = -1;
	}
	print_links(rooms, count_rooms);
	return (set_new_paths(rooms, count_rooms, count_paths, end_room));
	/*
	 * количество однонаправленных узлов из конечной вершины - количество новых путей.
	 *
	 */
}

t_path			*get_another_paths(t_lemin **lemin, int count_rooms)
{
	t_path		*new_path;
	int 		count_paths;

	count_paths = 1;
	new_path = get_new_paths((*lemin)->rooms, count_rooms, count_paths);//Bellman-Ford
	while ((*lemin)->count_ants > count_paths && new_path)
	{
		free((*lemin)->paths->roomnum_path);
		free((*lemin)->paths);
		(*lemin)->paths = new_path;
		new_path = NULL;//get_new_paths((*lemin)->rooms, count_rooms, ++count_paths);
	}
	return (new_path);
}
