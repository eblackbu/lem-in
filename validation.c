#include "lem-in.h"

/*
 * Проверка на муравьев в первой строке
 */
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
	if (ants < 0)
		exit(-1);
	return (ants);
}

/*
 * Проверяем количество муравьев, записываем в структуру. Проверяем всю карту, если возвращено не NULL,
 * значит карта валидна на этапе файла (проверено, что нет совпадающих вершин, нет одинаковых связей,
 * есть начальная и конечная вершина, но не проверено, есть ли путь до конечной вершины)
 */
t_lemin			*validation(void)
{
	t_lemin		*lemin;

	if (!(lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		exit(-1);
	lemin->count_ants = check_ants();
	check_map(&lemin);
	if (lemin->map)
		return(lemin);
	else
		{
		ft_putstr_fd("ERROR\n", 2);// когда писать error?
		exit(-1);
	}
}