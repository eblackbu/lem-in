#include "lem-in.h"

int 			get_len_to_end(t_graph **graph, int count_rooms, int roomnum)
{
	int 		i;

	i = 0;
	while (i < count_rooms)
	{
		if (graph[roomnum][i].link)
		{
			if (graph[i][0].bfs_lvl == MAX_INT)
				return (1);
			else if (graph[i][0].bfs_lvl > graph[roomnum][0].bfs_lvl)
				return (1 + get_len_to_end(graph, count_rooms, i));
		}
		i++;
	}
	return (MAX_INT);
}

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
	int 	len_first;
	int 	len_second;

	j = 0;
	while (j < count_rooms)
	{
		if (graph[i][j].link && graph[i][0].bfs_lvl == graph[j][0].bfs_lvl)
		{
			len_first = get_len_to_end(graph, count_rooms, i);
			len_second = get_len_to_end(graph, count_rooms, j);
			graph[i][j].link = len_first > len_second ? -1 : 1; //TODO Найти длину пути до конца, выбрать наименьшую
			graph[j][i].link = len_first > len_second ? 1 : -1;
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

t_graph			**del_dead_ends(t_graph **graph, int count_rooms)//TODO Проблема здесь!!
{
	int		i;
	int 	flag;

	i = 0;
	flag = 0;
	while (i < count_rooms)
	{
		if (count_output_links(graph, count_rooms, i) == 0 && graph[i][0].bfs_lvl != -1 && graph[i][0].bfs_lvl != MAX_INT)
		{
			graph[i][0].bfs_lvl = -1;
			graph = del_all_links(graph, count_rooms, i);
			flag++;
		}
		else
			i++;
		if (i == count_rooms && flag)
		{
			flag = 0;
			i = 0;
		}
	}
	return (graph);
}

t_path			**get_solution(t_graph **graph, int count_rooms)
{
	//print_links(graph, count_rooms);
	graph = del_unused_links(graph, count_rooms);//TODO разобраться со связями одного уровня глубины
	graph = del_dead_ends(graph, count_rooms);
	graph = find_input_forks(graph, count_rooms);
	graph = find_output_forks(graph, count_rooms);
	//print_links(graph, count_rooms);
	return (get_paths(graph, count_rooms));
}