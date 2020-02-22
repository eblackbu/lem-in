#include <stdio.h>
#include "lem-in.h"

/*
void 			print_links(t_room *rooms, int count_rooms)
{
	int i = 0;
	t_link	*tmp;

	while (i < count_rooms)
	{
		tmp = rooms[i].links;

		printf("name=%5s, number=%d bfs=%-10d, distance=%-10d, in_use=%d, ", rooms[i].name, i, rooms[i].bfs_lvl, rooms[i].dist, rooms[i].in_use);
		if (rooms[i].prev)
			printf(" prev=%2d, next=%2d, ", rooms[i].prev->number, rooms[i].next->number);
		else
			printf("                   ");
		if (rooms[i].new_prev)
			printf(" new_prev=%2d, ", rooms[i].new_prev->number);
		else
			printf("               ");
		if (rooms[i].new_next)
			printf("new_next=%2d, ", rooms[i].new_next->number);
		else
			printf("              ");
		while (tmp)
		{
			printf("weight %2d to %d, ", tmp->weight, tmp->roomnum);
			tmp = tmp->next;
		}
		i++;
		printf("\n");
	}
	printf("\n");
}
*/

void	error_exit(void)
{
	ft_putendl_fd("ERROR", 2);
	exit(-1);
}

int		main(int ac, char **av)
{
	t_lemin		*lemin;
	int 		count_rooms;
	int 		count_paths;

	//freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map", "r", stdin);
	lemin = validation();
	lemin->paths = get_first_path(lemin, get_count_rooms(lemin->list), 0);
	count_rooms = get_count_rooms(lemin->list);
	get_another_paths(&lemin, count_rooms, &count_paths);
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		print_paths(lemin->paths, lemin->rooms, count_paths);
	print_solution(lemin, lemin->count_ants, count_paths);
	free_all(lemin, count_rooms, count_paths);
	return (0);
}

