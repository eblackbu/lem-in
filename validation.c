#include "lem-in.h"

long long		check_ants(void)
{
	long long	ants;
	char 		*line;
	char 		*number;

	if (get_next_line(0, &line) < 1)
	{
		ft_putstr_fd("ERROR\n", 2);// когда писать error?
		exit(-1);
	}
	number = ft_itoa(ft_atoi(line));
	if (!ft_strcmp(line, number) && ft_strcmp(line, "0"))
		ants = ft_atoi(line);
	else
		ants = 0;
	ft_strdel(&line);
	ft_strdel(&number);
	if (ants <= 0)
		exit(-1);
	return (ants);
}

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

t_lemin			*validation(void)
{
	t_lemin		*lemin;

	if (!(lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		exit(-1);
	lemin->count_ants = check_ants();
	check_map(&lemin);
	if (lemin->list)
		return(lemin);
	else
	{
		ft_putendl_fd("ERROR", 2);// когда писать error?
		exit(-1);
	}
}