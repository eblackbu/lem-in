#include "lem-in.h"

t_room			*set_info_links(t_room *rooms, t_roomlist *list, int count_rooms)
{
	t_roomlist	*tmp;
	int 		i;

	i = 0;
	tmp = list;
	while (i < count_rooms)
	{
		rooms[i].number = i;
		rooms[i].name = tmp->room->name;
		rooms[i].bfs_lvl = tmp->room->bfs_lvl;
		rooms[i].dist = rooms[i].bfs_lvl != 0 ? MAX_INT : 0;
		rooms[i].links = NULL;
		rooms[i].prev = NULL;
		rooms[i].next = NULL;
		rooms[i].new_prev = NULL;
		rooms[i].new_next = NULL;
		i++;
		tmp = tmp->next;
	}
	return (rooms);
}

t_room			*init_links(int count_rooms, t_roomlist *map)
{
	t_room		*rooms;

	if (!(rooms = (t_room*)malloc(sizeof(t_room) * count_rooms)))
		exit (-1);
	return (set_info_links(rooms, map, count_rooms));
}

int 			set_link(int i, int j, t_room *rooms)
{
	rooms[i].links = add_new_link(rooms[i].links, 1, j);
	rooms[j].links = add_new_link(rooms[j].links, 1, i);
	/*
	if (rooms[i].edges[j].link == 1 || rooms[j].edges[i].link == 1 )
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	rooms[i].edges[j].link = 1;
	rooms[i].edges[j].weight = 1;
	rooms[j].edges[i].link = 1;
	rooms[j].edges[i].weight = 1;
	 */
	return (1);
}

int				check_link(t_lemin **lemin, char *linkline, int count_rooms)
{
	int 		i;
	int 		j;
	size_t 		len;

	i = 0;
	if (linkline[0] == '#')
		return (1);
	while (i < count_rooms && ft_strcmp(linkline, (*lemin)->rooms[i].name) != '-')
		i++;
	if (i == count_rooms)
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	j = 0;
	len = ft_strlen((*lemin)->rooms[i].name) + 1;
	while (j < count_rooms && ft_strcmp(&linkline[len], (*lemin)->rooms[j].name))
		j++;
	if (j == count_rooms)
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	return (set_link(i, j, (*lemin)->rooms));
}