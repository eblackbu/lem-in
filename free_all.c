#include "lem-in.h"

void		del_roomlist(t_roomlist **map)
{
	t_roomlist	*tmp;

	tmp = (*map)->next ? (*map)->next : NULL;
	while (*map)
	{
		ft_strdel(&(*map)->room->name);
		free((*map)->room);
		free(*map);
		*map = tmp;
		if (tmp)
			tmp = tmp->next;
	}
}

void 		del_all_links(t_room *room)
{
	t_link	*tmp;

	tmp = room->links;
	while (tmp)
	{
		room->links = tmp->next;
		free(tmp);
		tmp = room->links;
	}
}

void 		del_all_rooms(t_room **rooms, int count_rooms)
{
	int		i;

	i = 0;
	while (i < count_rooms)
	{
		del_all_links(rooms[i]);
		i++;
	}
	free(*rooms);
}

void		del_all_paths(t_path **paths, int count_paths)
{
	int 	i;

	i = 0;
	while (i < count_paths)
	{
		free((*paths)[i].roomnum_path);
		i++;
	}
	free(*paths);
}

void		free_all(t_lemin *lemin, int count_rooms, int count_paths)
{
	del_roomlist(&lemin->list);
	del_all_rooms(&lemin->rooms, count_rooms);
	del_all_paths(&lemin->paths, count_paths);
	free(lemin);
}