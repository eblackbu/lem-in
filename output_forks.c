#include "lem-in.h"

//TODO Убрать все ветки на выход через дейкстру, проходить начиная с последнего уровня и до первого (не нулевого)

int 		get_path_len(t_graph **graph, int count_rooms, int roomnum)
{
	int 	len;

	len = 1;
	while (graph[roomnum][0].bfs_lvl != MAX_INT)
	{
		roomnum = find_first_output(graph, count_rooms, roomnum);
		len++;
	}
	return (roomnum);
}

t_graph		**del_output_fork(t_graph **graph, int count_rooms, int roomnum, int needed_output)
{
	int 	i;
	int 	tmp_link;
	int 	tmp_room;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[roomnum][i].link == 1 && i != needed_output)
		{
			graph[roomnum][i].link = 0;
			graph[i][roomnum].link = 0;
			tmp_room = i;
			while (count_output_links(graph, count_rooms, tmp_room) == 1 && graph[tmp_room][0].bfs_lvl)
			{
				tmp_link = find_first_output(graph, count_rooms, tmp_room);
				graph[tmp_link][tmp_room].link = 0;
				graph[tmp_room][tmp_link].link = 0;
				tmp_room = tmp_link;
			}
		}
		i++;
	}
	return (graph);
}

t_graph		**check_output(t_graph **graph, int count_rooms, int roomnum)
{
	int		j;
	int 	best_room;
	int 	min_path;
	int		tmp_path;

	if (count_output_links(graph, count_rooms, roomnum) > 1)
	{
		j = 0;
		best_room = -1;
		min_path = MAX_INT;
		while (j < count_rooms)
		{
			if (graph[roomnum][j].link == -1)
			{
				tmp_path = get_path_len(graph, count_rooms, j);
				best_room = (min_path > tmp_path) ? best_room : j;
				min_path = (min_path > tmp_path) ? tmp_path : min_path;
			}
			j++;
		}
		return (del_output_fork(graph, count_rooms, roomnum, best_room));
	}
	return (graph);
}

t_graph		**find_output_forks(t_graph **graph, int count_rooms)
{
	int 	i;
	int 	layer;

	/*
	 * Пройтись по всем вершинам, начиная с вершин последнего уровня глубины.
	 * Если есть вилка на выход, проверить длину пути у каждого и оставить наименьший
	 */
	layer = get_max_layer(graph, count_rooms);
	while (layer)
	{
		i = 0;
		while (i < count_rooms)
		{
			if (graph[i][0].bfs_lvl == layer)
			{
				graph = check_output(graph, count_rooms, i);
			}
			i++;
		}
		layer--;
	}
	return (graph);
}
