#include "lem-in.h"

int			is_fast_path(t_path *paths, long long count_ants, int path_val)
{
	int 	i;
	int		len;

	i = 0;
	len = 0;
	if (count_ants == 0)
		return (0);
	while (paths[i].length < paths[path_val].length)
	{
		len += paths[path_val].length - paths[i].length;
		i++;
	}
	return (count_ants > len ? 1 : 0);
}

int		print_ant_move(t_path path, t_room *graph, int room, int flag_space)
{
	if (flag_space)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr((int)path.roomnum_path[room].antnum);
	ft_putchar('-');
	ft_putstr(graph[path.roomnum_path[room].roomnum].name);
	return (1);
}

int			make_pathstep(t_lemin **lemin, int path_val, long long all_ants, int flag_space)
{
	int		i;
	int		moves;

	i = (*lemin)->paths[path_val].length - 1;//TODO передвинуть всех муравьев на один шаг и вывести на экран данные шаги
	moves = 0;
	while (i >= 0)
	{
		if (i == 0 && is_fast_path((*lemin)->paths, (*lemin)->count_ants, path_val))
		{
			(*lemin)->count_ants--;
			(*lemin)->paths[path_val].roomnum_path[i].is_ant_here = 1;
			(*lemin)->paths[path_val].roomnum_path[i].antnum = all_ants - (*lemin)->count_ants;
			moves += print_ant_move((*lemin)->paths[path_val], (*lemin)->rooms, i, flag_space);
			flag_space++;
		}
		else if (i && (*lemin)->paths[path_val].roomnum_path[i - 1].is_ant_here > 0 &&
				 ((*lemin)->paths[path_val].roomnum_path[i].is_ant_here == 0 || i == (*lemin)->paths[path_val].length - 1))
		{
			(*lemin)->paths[path_val].roomnum_path[i - 1].is_ant_here = 0;
			(*lemin)->paths[path_val].roomnum_path[i].is_ant_here = 1;
			(*lemin)->paths[path_val].roomnum_path[i].antnum = (*lemin)->paths[path_val].roomnum_path[i - 1].antnum;
			moves += print_ant_move((*lemin)->paths[path_val], (*lemin)->rooms, i, flag_space);
			flag_space++;
		}
		i--;
	}
	return (moves);
}

int			make_step(t_lemin *lemin, int count_paths, long long all_ants)
{
	int		i;
	int		tmp_flag;

	i = 0;
	tmp_flag = 0;
	while (i < count_paths)
	{
		tmp_flag += make_pathstep(&lemin, i++, all_ants, tmp_flag);
	}
	if (tmp_flag)
		ft_putchar('\n');
	return (tmp_flag);
}

void		print_solution(t_lemin *lemin, long long count_ants, int count_rooms, int count_paths)
{
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = make_step(lemin, count_paths, count_ants);
	}
	//TODO free_all
}

void		sort_paths(t_path **paths, int count_paths)//TODO изменить на нормальную сортировку
{
	t_path	tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < count_paths - 1)
	{
		if ((*paths)[i].length > (*paths)[i + 1].length)
		{
			tmp = (*paths)[i];
			(*paths)[i] = (*paths)[i + 1];
			(*paths)[i + 1] = tmp;
			flag++;
		}
		i++;
		if (i == count_paths - 1 && flag)
		{
			i = 0;
			flag = 0;
		}
	}
}