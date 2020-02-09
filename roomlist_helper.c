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
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

/*
 * Удаление списка с комнатами
 */
void		del_all_rooms(t_roomlist **map)
{
	t_roomlist	*tmp;

	tmp = (*map)->next ? (*map)->next : NULL;
	while (*map)
	{
		ft_strdel(&(*map)->room->name);
		if ((*map)->room->input_ways)
			free((*map)->room->input_ways);
		if ((*map)->room->input_ways)
			free((*map)->room->output_ways);
		free((*map)->room);
		*map = tmp;
		tmp = tmp->next;
	}
}

/*
 * Добавление новой комнаты в конец списка
 */
void 		add_new_room(t_roomlist **map, char *line, int start_end)
{
	int			num;
	t_roomlist	*tmp_map;

	num = 0;
	tmp_map = *map;
	while (tmp_map)
	{
		num++;
		tmp_map = tmp_map->next;
	}
	if (!(tmp_map = (t_roomlist*)malloc(sizeof(t_roomlist))))
		exit(-1);
	tmp_map->room = init_room(num, line, start_end);
	tmp_map->next = NULL;
	if (!(check_nameplace(map, tmp_map->room->name, tmp_map->room->x, tmp_map->room->y)))
	{
		del_all_rooms(map);
		ft_putstr_fd("ERROR", 2);
		exit(-1);
	}
}

