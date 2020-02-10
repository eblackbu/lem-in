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

#include <stdio.h>
void 			print_links(t_graph **graph, int count_rooms)
{
	int i = 0;
	int j = 0;
	while (i < count_rooms)
	{
		j = 0;
		while (j < count_rooms)
		{
			if (j == 0)
				printf("\nname=%s, number=%d bfs=%d", graph[i][j].name, i, graph[i][j].bfs_lvl);
			printf(" %d", graph[i][j].link);
			j++;
		}
		i++;
	}
}

// TODO разобраться как хранить данные. Список оставлять опасно, очень долго будем искать и менять информацию о связях.
// Возможно, есть смысл сделать матрицу из структур, где помимо связей будет храниться информация о глубине вершины, и работат только с ней
void			get_links(t_lemin **lemin, char *linkline)
{
	int 		count_rm;

	count_rm = get_count_rooms((*lemin)->map);
	(*lemin)->links = init_links(count_rm, (*lemin)->map);
	print_links((*lemin)->links, count_rm);
	while (check_links(lemin, linkline, count_rm))
	{
		ft_strdel(&linkline);
		if (get_next_line(0, &linkline) < 1)
			break ;
	}
	print_links((*lemin)->links, count_rm);
}

/*
 * Создается список комнат и записывается информация о связях в матрицу смежности. Get_rooms возвращает первую строку,
 * которая не комментарий и не комната (строка со связью, в валидном варианте).
 */
void			check_map(t_lemin **lemin)
{
	t_roomlist		*roomlist;
	char 			*first_link;

	roomlist = NULL;
	first_link = get_rooms(&(*lemin)->map);
	get_links(lemin, first_link);
}