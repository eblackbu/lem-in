#include <stdio.h>
#include "lem-in.h"

#include <stdio.h>
void 			print_count_links(t_graph **graph, int count_rooms)
{
	int i = 0;

	FILE *fp = fopen("graph_map", "a");
	while (i < count_rooms)
	{
		if (count_input_links(graph, count_rooms, i) && !count_output_links(graph, count_rooms, i))
		{
			fprintf(fp,"%d, %d - in, %d - out\n", i, count_input_links(graph, count_rooms, i), count_output_links(graph, count_rooms, i));
		}
		i++;
	}
	fprintf(fp, "\n\n\n\n");
	fclose(fp);
}

void 	print_paths(t_graph **graph, t_path **paths, int count_paths)
{
	int i = 0;
	int j;

	while (i < count_paths)
	{
		j = 0;
		printf("Path %d: length: %d ", i, paths[i]->length);
		while (j < paths[i]->length)
		{
			printf("[%s]-", graph[paths[i]->roomnum_path[j++].roomnum][0].name);
		}
		printf("\n");
		i++;
	}
}

int		main()
{
	t_lemin		*lemin;
	t_path		**paths;

	//freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/maps/valid/difficult/three_ways.map", "r", stdin);
	lemin = validation();

	//TODO проверка, есть ли хоть один путь. Если муравей один, сделать дейкстру.
	//TODO сега на проверке связей, исправить. Проходит, если несколько конечных комнат и начальных.
	//
	lemin->links = set_bfs_levels(lemin->links, get_count_rooms(lemin->map), 0);
	/*
	 * if lemin->count_ants == 1
	 * 		paths = get_digstra();
	 * 	else
	 */
	lemin->paths = get_solution(lemin->links, get_count_rooms(lemin->map));
	//print_paths(lemin->links, lemin->paths, count_input_links(lemin->links, get_count_rooms(lemin->map), get_last_room(lemin->links, get_count_rooms(lemin->map))));
	print_solution(lemin, lemin->count_ants);
	free_all(lemin, get_count_rooms(lemin->map), count_input_links(lemin->links, get_count_rooms(lemin->map), get_last_room(lemin->links, get_count_rooms(lemin->map))));
	return (0);
}

