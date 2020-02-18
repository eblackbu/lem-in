#include <stdio.h>
#include "lem-in.h"

void 			print_paths(t_path *paths, t_room *rooms, int count_paths)
{
	int 	i;
	int		j;

	i = 0;
	while (i < count_paths)
	{
		j = 0;
		while (j < paths[i].length)
		{
			printf("[%s]-", rooms[paths[i].roomnum_path[j].roomnum].name);
			j++;
		}
		i++;
		printf("\n");
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
			{
				printf("name=%5s, number=%d bfs=%-10d, distance=%-10d, ", rooms[i].name, i, rooms[i].bfs_lvl, rooms[i].dist);
				if (rooms[i].parent)
					printf("parent = %2d,", rooms[i].parent->number);
				else
					printf("            ");
				if (rooms[i].prev)
					printf(" prev=%2d, next=%2d, ", rooms[i].prev->number, rooms[i].next->number);
				else
					printf("                   ");
			}
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
	print_paths(lemin->paths, lemin->rooms, 1);

	get_another_paths(&lemin, get_count_rooms(lemin->list));
	print_paths(lemin->paths, lemin->rooms, 2);
	//print_paths(lemin->links, lemin->paths, count_input_links(lemin->links, get_count_rooms(lemin->list), get_last_room(lemin->links, get_count_rooms(lemin->list))));
	//print_solution(lemin, lemin->count_ants);
	return (0);
}

