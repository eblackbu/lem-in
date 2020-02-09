#include "lem-in.h"

int				**init_links(int count_rooms)
{
	int 		i;
	int 		j;
	int 		**links;

	i = 0;
	if (!(links = (int**)malloc(sizeof(int*) * count_rooms)))
		exit (-1);
	while (i < count_rooms)
	{
		if (!(links[i] = (int*)malloc(sizeof(int) * count_rooms)))
			exit (-1);
		j = 0;
		while (j < count_rooms)
			links[i][j++] = 0;
		i++;
	}
	return (links);
}

int				count_rooms(t_roomlist *roomlist)
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


// TODO разобраться как хранить данные. Список оставлять опасно, очень долго будем искать и менять информацию о связях.
// Возможно, есть смысл сделать матрицу из структур, где помимо связей будет храниться информация о глубине вершины, и работат только с ней
void			get_links(t_lemin **lemin, char *linkline)
{
	(*lemin)->links = init_links(count_rooms((*lemin)->map));
	while (check_link(first_link))
	{
		set_link(lemin, linkline);
		ft_strdel(&linkline);
		if (get_next_line(0, &linkline) < 1)
			break ;
	}
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
	get_links(lemin, first_link);//TODO распарсить связи в матрицу по количеству комнат, записать в каждую комнату глубину, количество выходов и входов
}