#include "lem-in.h"

int			add_children_layers(t_graph ***graph, int count_rooms, int roomnum)
{
	int 	j;
	int 	k;
	int 	flag;

	j = 0;
	flag = 0;
	while (j < count_rooms)
	{
		if ((*graph)[roomnum][j].link)
		{
			if ((*graph)[j][0].bfs_lvl == -1)
			{
				k = 0;
				while (k < count_rooms)
					(*graph)[j][k++].bfs_lvl = (*graph)[roomnum][0].bfs_lvl + 1;
				flag = 1;
			}
			if ((*graph)[j][0].bfs_lvl > (*graph)[roomnum][0].bfs_lvl)
			{
				(*graph)[roomnum][j].link = -1;
				(*graph)[j][roomnum].link = 1;
			}
		}
		j++;
	}
	return (flag);
}

t_graph 	**set_bfs_levels(t_graph **graph, int count_rooms, int layer)
{
	int		j;
	int 	flag;

	j = 0;
	flag = 0;
	while (j < count_rooms)
	{
		if (graph[j][0].bfs_lvl == layer)
			/*
			 * Если мы нашли вершину с таким уровнем глубины, добавляем ставим всем ее дочерним вершинам +1 от данного уровня глубины
			 */
		{
			flag += add_children_layers(&graph, count_rooms, j);
		}
		j++;
	}
	if (flag)
		return (set_bfs_levels(graph, count_rooms, layer + 1));
	return (graph);
}