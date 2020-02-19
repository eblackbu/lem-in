#include "lem-in.h"

t_room		set_distance(t_room *rooms, int i, int j)
{
	if (rooms[j].bfs_lvl != 0 && rooms[i].dist != MAX_INT && rooms[j].dist > rooms[i].dist + rooms[i].edges[j].weight)
	{
		rooms[j].dist = rooms[i].dist + rooms[i].edges[j].weight;
		if (rooms[i].bfs_lvl != 0)
			rooms[i].new_next = &rooms[j];
		if (rooms[j].bfs_lvl != MAX_INT)
			rooms[j].new_prev = &rooms[i];
	}
	/*
	 * TODO поставить поле in_use в структуру комнат. Проверять, если i - in_use, а j - !in_use, то если prev для i - !in_use, то такой связи нет
	 */
	return (rooms[j]);
}

t_room		*get_distance(t_room *rooms, int count_rooms)
{
	int		i;
	int 	j;

	i = 0;
	while (i < count_rooms)
	{
		j = 0;
		while (j < count_rooms)
		{
			if (rooms[i].edges[j].link)
				rooms[j] = set_distance(rooms, i, j);
			j++;
		}
		i++;
	}
	return (rooms);
}

t_path		*get_new_paths(t_room *rooms, int count_rooms, int count_paths)
{
	int		i;
	t_path	*new_path;

	i = 0;
	new_path = NULL;
	while (i < count_rooms)
	{
		rooms = get_distance(rooms, count_rooms);//TODO переписать связи на список, а не массив смежности
		i++;
	}
	//print_links(rooms, count_rooms);//TODO записать новые пути через prev/next, попутно обрезая двухсторонние обратные линии.
	if (rooms[get_end_room(rooms, count_rooms)].dist != MAX_INT)
		new_path = del_overused_edges(rooms, count_rooms, count_paths);
	return (new_path);
}
