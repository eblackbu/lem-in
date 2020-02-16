#include "lem-in.h"

char		*get_name(char *roomline)
{
	char 	*name;
	int		n;

	n = 0;
	while (roomline[n] != ' ')
		n++;
	name = ft_strnew(n);
	ft_strncpy(name, roomline, n);
	return (name);
}

int 		get_coordinate_x(char *roomline)
{
	int		n;

	n = 0;
	while (roomline[n] != ' ')
		n++;
	return (ft_atoi(&roomline[n + 1]));
}

int 		get_coordinate_y(char *roomline)
{
	int		n;

	n = 0;
	while (roomline[n] != ' ')
		n++;
	n++;
	while (roomline[n] != ' ')
		n++;
	return (ft_atoi(&roomline[n + 1]));
}

/*
 * Создается структура комнаты по входным данным:
 * 1) номер по порядку(для выделения памяти под матрицу смежности в дальнейшем)
 * 2) строка с информацией о комнате - название и координаты
 * 3) start_end - флаг с указанием, является ли эта комната стартовой или конечной
 */
t_room		*init_room(int num, char *roomline, int start_end)
{
	t_room	*new_room;

	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		exit(-1);
	new_room->number = num;
	new_room->name = get_name(roomline);
	new_room->x = get_coordinate_x(roomline);
	new_room->y = get_coordinate_y(roomline);
	if (start_end)
		new_room->bfs_lvl = (start_end == START_ROOM ? 0 : MAX_INT);
	else
		new_room->bfs_lvl = -1;
	return (new_room);
}
