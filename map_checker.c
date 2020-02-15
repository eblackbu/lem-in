#include "lem-in.h"

int				get_count_rooms(t_roomlist *roomlist)
{
	int 		count;
	t_roomlist	*tmp;

	count = 0;
	tmp = roomlist;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int				check_start_end(t_graph **graph, int count_rooms)
{
	int 	i;
	int		start_rooms;
	int 	end_rooms;

	i = 0;
	start_rooms = 0;
	end_rooms = 0;
	while (i < count_rooms)
	{
		if (graph[i][0].bfs_lvl == 0)
			start_rooms++;
		else if (graph[i][0].bfs_lvl == MAX_INT)
			end_rooms++;
		i++;
	}
	if (start_rooms == 1 && end_rooms == 1)
		return (1);
	return (0);
}

void			get_links(t_lemin **lemin, char *linkline)
{
	int 		count_rooms;

	count_rooms = get_count_rooms((*lemin)->map);
	(*lemin)->links = init_links(count_rooms, (*lemin)->map);
	while (check_link(lemin, linkline, count_rooms))
	{
		ft_strdel(&linkline);
		if (get_next_line(0, &linkline) < 1)
			break ;
	}
	if (!check_start_end((*lemin)->links, count_rooms))
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
}

/*
 * Создается список комнат и записывается информация о связях в матрицу смежности. Get_rooms возвращает первую строку,
 * которая не комментарий и не комната (строка со связью, в валидном варианте).
 */
void			check_map(t_lemin **lemin)
{
	char 			*first_link;

	(*lemin)->map = NULL;
	if (!(first_link = get_rooms(&(*lemin)->map)))
	{
		ft_putendl_fd("ERROR", 2);
		exit(-1);
	}
	get_links(lemin, first_link);
}