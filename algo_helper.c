#include "lem-in.h"

int				get_max_layer(t_graph **graph, int count_rooms)
{
	int 	i;
	int 	max_layer;

	i = 0;
	max_layer = 0;
	while (i < count_rooms)
	{
		if (max_layer < graph[i][0].bfs_lvl && graph[i][0].bfs_lvl != MAX_INT)
			max_layer = graph[i][0].bfs_lvl;
		i++;
	}
	return (max_layer);
}

int 			find_first_output(t_graph **graph, int count_rooms, int roomnum)
{
	int 		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[roomnum][i].link == -1)
			return (i);
		i++;
	}
	exit(-1);
}

int 			find_first_input(t_graph **graph, int count_rooms, int roomnum)
{
	int 		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[roomnum][i].link == 1)
			return (i);
		i++;
	}
}

int				count_input_links(t_graph **graph, int count_rooms, int i)
{
	int 	j;
	int 	count_input;

	j = 0;
	count_input = 0;
	while (j < count_rooms)
	{
		if (graph[i][j].link == 1)
			count_input++;
		j++;
	}
	return (count_input);
}

int				count_output_links(t_graph **graph, int count_rooms, int i)
{
	int 	j;
	int 	count_output;

	j = 0;
	count_output = 0;
	while (j < count_rooms)
	{
		if (graph[i][j].link == -1)
			count_output++;
		j++;
	}
	return (count_output);
}

int 			check_all_forks(t_graph **graph, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[i][0].bfs_lvl != 0 && count_input_links(graph, count_rooms, i) != 1)
			return (1);
		if (graph[i][0].bfs_lvl != MAX_INT && count_output_links(graph, count_rooms, i) != 1)
			return (1);
		i++;
	}
	return (0);
}