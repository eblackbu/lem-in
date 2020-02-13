#include "lem-in.h"

void		free_all_rooms(t_roomlist **map)
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

void 	free_all_links(t_graph ***graph, int count_paths)
{
	int 	i;

	i = 0;
	while (i < count_paths)
		free((*graph)[i++]);
	free(*graph);
}

void	free_all_paths(t_path **paths, int count_paths)
{
	int 	i;

	i = 0;
	while (i < count_paths)
	{
		free(paths[i]->roomnum_path);
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	free_all(t_lemin *lemin, int count_rooms, int count_paths)
{
	free_all_rooms(&lemin->map);
	free_all_links(&lemin->links, count_rooms);
	free_all_paths(lemin->paths, count_paths);
	free(lemin);
}

