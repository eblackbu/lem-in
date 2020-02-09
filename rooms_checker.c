#include "lem-in.h"

/*
 * Проверка на число
 */
int				is_number(char *line)
{
	char 	*val;

	val = ft_itoa(ft_atoi(line));
	if (ft_strcmp(val, line) == 32)
	{
		ft_strdel(&val);
		return (1);
	}
	else
	{
		ft_strdel(&val);
		return (0);
	}
}

/*
 * Подсчет количества пробелов в строке
 */
int 			count_spaces(char *roomline)
{
	int 	n;
	int		count;

	n = 0;
	count = 0;
	while(roomline[n])
	{
		if (roomline[n] == ' ')
			count++;
		n++;
	}
	return (count);
}

/*
 * Проверка, является ли строка комментарием либо строкой с комнатой
 */
int				check_roomline(char *roomline)
{
	if (roomline[0] == '#')
		return (1);
	if (count_spaces(roomline) == 2)
	{
		if (is_number(&ft_strchr(roomline, ' ')[1]) && is_number(&ft_strrchr(roomline, ' ')[1]) && roomline[0] != 'L')
			return (1);
	}
	return (0);
}

/*
 * Проверка на комментарий, является ли следующая комната стартовой или конечной
 */
int				get_start_end(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (START_ROOM);
	else if (!ft_strcmp(line, "##end"))
		return (END_ROOM);
	return (0);
}

/*
 * Создается список комнат из исходного файла.
 * Как только встречается строка связи, она возвращается
 */
char 			*get_rooms(t_roomlist **map)
{
	int			start_end;
	char 		*line;

	start_end = 0;
	line = NULL;
	if (get_next_line(0, &line) < 1)
		exit(-1);
	while (check_roomline(line))
	{
		if (line[0] == '#')
			start_end = get_start_end(line);
		else
		{
			add_new_room(map, line, start_end);
			start_end = 0;
		}
		ft_strdel(&line);
		if (get_next_line(0, &line) < 1)
			break ;
	}
	return (line);
}