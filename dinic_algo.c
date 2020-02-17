#include "lem-in.h"

int			add_children_layers(t_room **rooms, int count_rooms, int roomnum)
{
	int 	j;
	int 	flag;

	j = 0;
	flag = 0;
	while (j < count_rooms)
	{
		if ((*rooms)[roomnum].edges[j].link)
		{
			if ((*rooms)[j].bfs_lvl == -1) //Если вершина еще не была посещена
			{
				(*rooms)[j].bfs_lvl = (*rooms)[roomnum].bfs_lvl + 1;
				flag = 1;
			}
		}
		j++;
	}
	return (flag);
}

int			get_first_path_length(t_room *rooms, int count_rooms)
{
	int 	end;
	int 	len;
	int		i;

	i = 0;
	len = MAX_INT - 1;
	end = get_end_room(rooms, count_rooms);
	while (i < count_rooms)
	{
		if (rooms[end].edges[i].link && rooms[i].bfs_lvl < len && rooms[i].bfs_lvl != -1)
			len = rooms[i].bfs_lvl + 1;
		i++;
	}
	if (len == MAX_INT - 1)
		exit(-1);
	return (len);
}

t_ant		*get_first_roomnum_path(t_room *rooms, int count_rooms, int len)
{
	t_ant	*path;
	int 	i;
	int		roomnum;

	if (!(path = (t_ant*)malloc(sizeof(t_ant) * len--)))
		exit(-1);
	roomnum = get_end_room(rooms, count_rooms);
	while (len >= 0)
	{
		path[len].roomnum = roomnum;
		path[len].is_ant_here = 0;
		i = 0;
		while (rooms[i].bfs_lvl != len || rooms[roomnum].edges[i].link == 0)
			i++;
		len--;
		if (rooms[i].bfs_lvl != 0)
			rooms[i].next = &rooms[roomnum];
		if (rooms[roomnum].bfs_lvl != MAX_INT)
			rooms[roomnum].prev = &rooms[roomnum];
		roomnum = i;
	}
	return (path);
}

t_path		*set_first_path(t_room *rooms, int count_rooms)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		exit(-1);
	path->length = get_first_path_length(rooms, count_rooms);
	path->roomnum_path = get_first_roomnum_path(rooms, count_rooms, path->length);
	switch_links(path, rooms, count_rooms);
	path->next = NULL;
	return (path);
}

t_path		*get_first_path(t_lemin *lemin, int count_rooms, int layer)
{
	int		j;
	int 	flag;

	j = 0;
	flag = 0;
	while (j < count_rooms)
	{
		if (lemin->rooms[j].bfs_lvl == layer)
			flag += add_children_layers(&lemin->rooms, count_rooms, j);
		j++;
	}
	if (flag)
		return (get_first_path(lemin, count_rooms, layer + 1));
	else
		return (set_first_path(lemin->rooms, count_rooms));
}
