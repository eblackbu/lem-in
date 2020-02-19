#include "lem-in.h"

int			add_children_layers(t_room **rooms, int count_rooms, int roomnum)
{
	/*
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
	 */
	int 	flag;
	t_link	*tmp;

	flag = 0;
	tmp = (*rooms)[roomnum].links;
	while (tmp)
	{
		if ((*rooms)[tmp->roomnum].bfs_lvl == -1)
		{
			(*rooms)[tmp->roomnum].bfs_lvl = (*rooms)[roomnum].bfs_lvl + 1;
			flag = 1;
		}
		tmp = tmp->next;
	}
	return (flag);
}

int			get_first_path_length(t_room *rooms, int count_rooms)
{
	/*
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
	*/

	int		len;
	int 	tmp_room;
	t_link	*tmp;

	len = MAX_INT - 1;
	tmp_room = get_end_room(rooms, count_rooms);
	tmp = rooms[tmp_room].links;
	while (tmp)
	{
		if (rooms[tmp->roomnum].bfs_lvl < len && rooms[tmp->roomnum].bfs_lvl != -1)
			len = rooms[tmp->roomnum].bfs_lvl + 1;
		tmp = tmp->next;
	}
	if (len == MAX_INT - 1)
		exit(-1);
	return (len);
}

t_ant		*get_first_roomnum_path(t_room *rooms, int count_rooms, int len)
{
	t_ant	*path;
	t_link	*tmp;
	int		roomnum;

	if (!(path = (t_ant*)malloc(sizeof(t_ant) * len--)))
		exit(-1);
	roomnum = get_end_room(rooms, count_rooms);
	while (len >= 0)
	{
		path[len].roomnum = roomnum;
		path[len].is_ant_here = 0;
		tmp = rooms[roomnum].links;
		while (tmp && rooms[tmp->roomnum].bfs_lvl != len)
			tmp = tmp->next;
		len--;
		if (rooms[tmp->roomnum].bfs_lvl != 0)
			rooms[tmp->roomnum].next = &rooms[roomnum];
		if (rooms[roomnum].bfs_lvl != MAX_INT)
			rooms[roomnum].prev = &rooms[tmp->roomnum];
		roomnum = tmp->roomnum;
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
