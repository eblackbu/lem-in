#include "lem-in.h"

t_room		*del_link(t_room *rooms, int room_first, int room_where)
{
	t_link	*tmp;
	t_link	*tmp_last;

	tmp = rooms[room_first].links;
	while (tmp->roomnum != room_where)
	{
		tmp_last = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		exit(-1);
	tmp_last->next = tmp->next;
	free(tmp);
	return (rooms);
}

t_link		*new_link(int weight, int room)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		exit(-1);
	new->roomnum = room;
	new->weight = weight;
	new->next = NULL;
	return (new);
}

t_link 		*add_new_link(t_link *links, int weight, int room)
{
	t_link	*tmp_last;
	t_link	*tmp_next;

	tmp_next = links;
	while (tmp_next)
	{
		tmp_last = tmp_next;
		tmp_next = tmp_next->next;
	}
	if (!links)
		links = new_link(weight, room);
	else
	{
		tmp_next = new_link(weight, room);
		tmp_last->next = tmp_next;
	}
	return (links);
}