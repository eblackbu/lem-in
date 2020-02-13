#include "lem-in.h"

t_graph			**set_info_links(t_graph **links, t_roomlist *map, int count_rooms)
{
	t_roomlist	*tmp;
	int 		j;

	tmp = map;
	while (tmp)
	{
		j = 0;
		while (j < count_rooms)
		{
			if (j == 0)
				links[tmp->room->number][j].name = tmp->room->name;
			links[tmp->room->number][j].bfs_lvl = tmp->room->bfs_level;
			j++;
		}
		tmp = tmp->next;
	}
	return (links);
}

t_graph			**init_links(int count_rooms, t_roomlist *map)
{
	int 		i;
	int 		j;
	t_graph		**links;

	i = 0;
	if (!(links = (t_graph**)malloc(sizeof(t_graph*) * count_rooms)))
		exit (-1);
	while (i < count_rooms)
	{
		if (!(links[i] = (t_graph*)malloc(sizeof(t_graph) * count_rooms)))
			exit (-1);
		j = 0;
		while (j < count_rooms)
			links[i][j++].link = 0;
		i++;
	}
	return (set_info_links(links, map, count_rooms));
}

int 			set_link(int i, int j, t_graph **graph)
{
	if (graph[i][j].link == 1 || graph[j][i].link == 1 )
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	graph[i][j].link = 1;
	graph[j][i].link = 1;
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
	while (i < count_rooms && ft_strcmp(linkline, (*lemin)->links[i][0].name) != '-')
		i++;
	if (i == count_rooms)
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	j = 0;
	len = ft_strlen((*lemin)->links[i][0].name) + 1;
	while (j < count_rooms && ft_strcmp(&linkline[len], (*lemin)->links[j][0].name))
		j++;
	if (j == count_rooms)
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	return (set_link(i, j, (*lemin)->links));
}