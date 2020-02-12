#include <stdio.h>
#include "lem-in.h"

void 	print_paths(t_path **paths, int count_paths)
{
	int i = 0;
	int j;

	while (i < count_paths)
	{
		j = 0;
		while (j < paths[i]->length)
		{
			printf("[%d]-", paths[i]->roomnum_path[j++]);
		}
		printf("\n");
		i++;
	}
}

int		main()
{
	t_lemin		*lemin;
	t_path		**paths;

	paths = NULL;
	freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map", "r", stdin);
	lemin = validation();

	//TODO проверка, есть ли хоть один путь. Если муравей один, сделать дейкстру.
	lemin->links = set_bfs_levels(lemin->links, get_count_rooms(lemin->map), 0);
	/*
	 * if lemin->count_ants == 1
	 * 		paths = get_digstra();
	 * 	else
	 */
	paths = get_solution(lemin->links, get_count_rooms(lemin->map));
	/*
	 * print_solution(lemin, paths);
	 * free_all(lemin, paths);
	 */
	return (0);
}

