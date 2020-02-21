#include <stdio.h>
#include "lem-in.h"

void 			print_paths(t_path *paths, t_room *rooms, int count_paths)
{
	int 	i;
	int		j;
	int 	len;

	i = 0;
	len = 0;
	while (i < count_paths)
	{
		len += paths[i].length;
		j = 0;
		printf("Path %d: ", i + 1);
		while (j < paths[i].length)
		{
			printf("[%s]-", rooms[paths[i].roomnum_path[j].roomnum].name);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("Average length of paths: %d\n", len / count_paths);
}

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

int 	get_count_paths(t_room *rooms, int count_rooms)
{
	int 	end;
	int 	count;
	t_link	*tmp;

	count = 0;
	end = get_end_room(rooms, count_rooms);
	tmp = rooms[end].links;
	while (tmp)
	{
		if (tmp->weight == -1)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int		main(int ac, char **av)
{
	t_lemin		*lemin;
	int 		count_rooms;
	int 		count_paths;

	//freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map", "r", stdin);
	lemin = validation();
	lemin->paths = get_first_path(lemin, get_count_rooms(lemin->list), 0);
//	print_links(lemin->rooms, get_count_rooms(lemin->list));
	//print_paths(lemin->paths, lemin->rooms, 1);
	count_rooms = get_count_rooms(lemin->list);
	get_another_paths(&lemin, count_rooms, &count_paths);
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		print_paths(lemin->paths, lemin->rooms, count_paths);//TODO Флаг дебага, поставить условие
	print_solution(lemin, lemin->count_ants, count_rooms, count_paths);
	return (0);
}

