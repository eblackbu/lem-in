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
				links[tmp->room->number][j].name = ft_strdup(tmp->room->name); //мб можно просто взять указатель
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

int 		set_links(int i, int j, t_graph **graph)
{
	graph[i][j].link = 1;
	graph[j][i].link = 1;
	return (1);
}

int			check_links(t_lemin **lemin, char *linkline, int count_rooms)
{
	int 		i;
	int 		j;
	size_t 		len;

	i = 0;
	while (ft_strcmp(linkline, (*lemin)->links[i][0].name) != '-' && i < count_rooms)
		i++;
	if (i == count_rooms)
		return (0);//первая комната не найдена
	j = 0;
	len = ft_strlen((*lemin)->links[i][0].name) + 1;
	while (ft_strcmp(&linkline[len], (*lemin)->links[j][0].name) && j < count_rooms)
		j++;
	if (j == count_rooms)
		return (0);//вторая комната не найдена
	return (set_links(i, j, (*lemin)->links));
}