#include <stdio.h>
#include "lem-in.h"

void 			print_paths(t_path *paths, t_room *rooms)
{
	int 	i;

	while (paths)
	{
		i = 0;
		while (i < paths->length)
		{
			printf("[%s]-", rooms[paths->roomnum_path[i].roomnum].name);
			i++;
		}
		printf("\n");
		paths = paths->next;
	}
}

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
				printf("name=%5s, number=%d bfs=%-10d, distance=%-10d", rooms[i].name, i, rooms[i].bfs_lvl, rooms[i].dist);
			printf(" %2d", rooms[i].edges[j].weight);
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
	int 		count_max;

	freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map3", "r", stdin);
	lemin = validation();
	lemin->paths = get_first_path(lemin, get_count_rooms(lemin->list), 0);
	print_links(lemin->rooms, get_count_rooms(lemin->list));
	print_paths(lemin->paths, lemin->rooms);

	//lemin->paths = get_another_paths(&lemin, get_count_rooms(lemin->list));
	//print_paths(lemin->links, lemin->paths, count_input_links(lemin->links, get_count_rooms(lemin->list), get_last_room(lemin->links, get_count_rooms(lemin->list))));
	//print_solution(lemin, lemin->count_ants);
	return (0);
}

