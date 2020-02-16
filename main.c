#include <stdio.h>
#include "lem-in.h"

void 			print_links(t_room *rooms, int count_rooms)
{
	int i = 0;
	int j = 0;
	while (i < count_rooms)
	{
		j = 0;
		while (j < count_rooms)
		{
			if (j == 0)
				printf("name=%s, number=%d bfs=%-10d, ", rooms[i].name, i, rooms[i].edges[j].link);
			printf(" %2d", rooms[i].edges[j].link);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("\n");
}

int		main()
{
	t_lemin		*lemin;

	freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map", "r", stdin);
	lemin = validation();
	print_links(lemin->rooms, get_count_rooms(lemin->list));
	/*
	 * if lemin->count_ants == 1
	 * 		paths = get_digstra();
	 * 	else
	 */
	//lemin->paths = get_solution(lemin->links, get_count_rooms(lemin->list));
	//print_paths(lemin->links, lemin->paths, count_input_links(lemin->links, get_count_rooms(lemin->list), get_last_room(lemin->links, get_count_rooms(lemin->list))));
	//print_solution(lemin, lemin->count_ants);
	return (0);
}

