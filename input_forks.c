#include "lem-in.h"
#include <stdio.h>

int				is_nice_way(t_graph **graph, int count_rooms, int roomnum)
{
	int 	tmp;

	tmp = roomnum;
	while (graph[roomnum][0].bfs_lvl)
	{
		if (count_output_links(graph, count_rooms, roomnum) > 1)
			return (-1);
		roomnum = find_first_input(graph, count_rooms, roomnum);
	}
	return (tmp);
}

t_graph			**del_input_fork(t_graph **graph, int count_rooms, int roomnum, int needed_input)
{
	int 	i;
	int 	tmp_link;
	int 	tmp_room;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[roomnum][i].link == 1 && i != needed_input)
		{
			graph[roomnum][i].link = 0;
			graph[i][roomnum].link = 0;
			tmp_room = i;
			while (graph[tmp_room][0].bfs_lvl != 0 && count_output_links(graph, count_rooms, tmp_room) == 0)
			{
				tmp_link = find_first_input(graph, count_rooms, tmp_room);
				graph[tmp_link][tmp_room].link = 0;
				graph[tmp_room][tmp_link].link = 0;
				tmp_room = tmp_link;
			}
		}
		i++;
	}
	return (graph);
}

t_graph			**check_input(t_graph **graph, int count_rooms, int i)
{
	int 	j;
	int		tmp_room;
	int 	best_room;
	int		inputs;

	inputs = count_input_links(graph, count_rooms, i);
	if (inputs > 1)
	{
		j = 0;
		best_room = -1;
		while (j < count_rooms)
		{
			if (graph[i][j].link == 1)
			{
				tmp_room = is_nice_way(graph, count_rooms, j); //для вершины, из которой был вход в проверяемую, смотрим, есть ли у нее ветки на выход и так до начала
				if (best_room < tmp_room)
					best_room = tmp_room;
			}
			j++;
		}
		if (best_room == -1)
			best_room = find_first_input(graph, count_rooms, i);
		return (del_input_fork(graph, count_rooms, i, best_room));
	}
	return (graph);
}

/*
** Начиная с первой вершины, пройтись по всем. Если есть вилка на входе, идти до начала по всем возможным путям,
** оставить тот, который без вилок выхода. Если все плохие, взять первый
*/
t_graph			**find_input_forks(t_graph **graph, int count_rooms)
{
	int i;
	int layer;
	int max_layer;

	layer = 1;
	max_layer = get_max_layer(graph, count_rooms);
	while (layer < max_layer + 1)
	{
		i = 0;
		while (i < count_rooms)
		{
			if (graph[i][0].bfs_lvl == layer)
			{
				graph = check_input(graph, count_rooms, i);
			}
			i++;
		}
		layer++;
	}
	return (graph);
}