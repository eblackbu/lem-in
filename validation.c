#include <fcntl.h>
#include "lem-in.h"

long long 		check_ants(void)
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
	if (ants < 0)
		exit(-1);
	return (ants);
}

t_lemin		validation(void)
{
	t_lemin		lemin;

	lemin.ants = check_ants();
	lemin.map = check_map();
	if (lemin.map)
		return(lemin);
	else
		{
		ft_putstr_fd("ERROR\n", 2);// когда писать error?
		exit(-1);
	}
}

