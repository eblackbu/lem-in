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

int			is_any_path(t_graph **graph, int count_rooms)
{
	int 	i;
	int		j;

	i = 0;
	while (graph[i][0].bfs_lvl != MAX_INT)
		i++;
	j = 0;
	while (j < count_rooms && graph[i][j].link == 0)
		j++;
	if (j == count_rooms)
		return (0);
	return (1);
}
/*
** Поиск в глубину. Рекурсивно, начиная с нулевого уровня глубины, ищем вершины-потомки от вершины с текущим уровнем глубины.
** Присваиваем данным вершинвм layer + 1. Если хотя бы одной вершине на данной итерации был присвоен уровень глубины, запускаем функцию с уровнем глубины layer + 1.
*/
t_graph 	**set_bfs_levels(t_graph **graph, int count_rooms, int layer)
{
	int		j;
	int 	flag;

	j = 0;
	flag = 0;
	while (j < count_rooms)
	{
		if (graph[j][0].bfs_lvl == layer)
			flag += add_children_layers(&graph, count_rooms, j);
		j++;
	}
	if (flag)
		return (set_bfs_levels(graph, count_rooms, layer + 1));
	else if (is_any_path(graph, count_rooms))
		return (graph);
	else
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
}