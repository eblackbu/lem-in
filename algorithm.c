#include "lem-in.h"

t_graph			**del_all_links(t_graph **graph, int count_rooms, int i)
{
	int		j;

	j = 0;
	while (j < count_rooms)
	{
		if (graph[i][j].link)
		{
			graph[i][j].link = 0;
			graph[j][i].link = 0;
		}
		j++;
	}
	return (graph);
}

t_graph			**del_samelayer_links(t_graph **graph, int count_rooms, int i)
{
	int		j;

	j = 0;
	while (j < count_rooms)
	{
		if (graph[i][j].link && graph[i][0].bfs_lvl == graph[j][0].bfs_lvl)
		{
			graph[i][j].link = 0;
			graph[j][i].link = 0;
		}
		j++;
	}
	return (graph);
}

t_graph			**del_unused_links(t_graph **graph, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[i][0].bfs_lvl == -1)
			graph = del_all_links(graph, count_rooms, i);
		else
			graph = del_samelayer_links(graph, count_rooms, i);
		i++;
	}
	return (graph);
}

t_graph			**del_dead_ends(t_graph **graph, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		if (count_output_links(graph, count_rooms, i) == 0 && graph[i][0].bfs_lvl != -1 && graph[i][0].bfs_lvl != MAX_INT)
		{
			graph[i][0].bfs_lvl = -1;
			graph = del_all_links(graph, count_rooms, i);
			i = 0;
		}
		else
			i++;
	}
	return (graph);
}

t_path			**get_solution(t_graph **graph, int count_rooms)
{
	graph = del_unused_links(graph, count_rooms);
	graph = del_dead_ends(graph, count_rooms);
	graph = find_input_forks(graph, count_rooms);
	graph = find_output_forks(graph, count_rooms);
	return (get_paths(graph, count_rooms));
}