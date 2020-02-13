#include "lem-in.h"

/*
 * Проверка, нет ли в списке комнаты с таким же названием, либо с такими же координатами
 */
int			check_nameplace(t_roomlist **map, char *name, int x, int y)
{
	t_roomlist	*tmp;

	tmp = *map;
	if (tmp)
	{
		while (tmp->next)
		{
			if (!ft_strcmp(name, tmp->room->name) || (x == tmp->room->x && y == tmp->room->y))
			{
				free_all_rooms(map);
				ft_putstr_fd("ERROR\n", 2);
				exit(-1);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}

/*
 * Добавление новой комнаты в конец списка
 */
void 		add_new_room(t_roomlist **map, char *line, int start_end)
{
	int			num;
	t_roomlist	*tmp_last;
	t_roomlist	*tmp_map;

	tmp_last = *map;
	num = tmp_last ? 1 : 0;
	while (tmp_last && tmp_last->next)
	{
		num++;
		tmp_last = tmp_last->next;
	}
	if (!(tmp_map = (t_roomlist*)malloc(sizeof(t_roomlist))))
		exit(-1);
	tmp_map->room = init_room(num, line, start_end);
	tmp_map->next = NULL;
	if (!tmp_last)
		*map = tmp_map;
	else
		tmp_last->next = tmp_map;
	check_nameplace(map, tmp_map->room->name, tmp_map->room->x, tmp_map->room->y);
}

