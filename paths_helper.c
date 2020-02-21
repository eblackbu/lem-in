#include "lem-in.h"

int 		is_better_solution(t_path *paths, int count_paths, int count_ants, int *prev_solu)
{
	int 	i;
	int 	new_solu;

	i = 0;
	new_solu = 0;
	while (i < count_paths)
	{
		new_solu += paths[i].length;
		if (paths[i].length > count_ants - i)
			return (0);
		i++;
	}
	new_solu += count_ants - 1;
	if (new_solu / count_paths < *prev_solu)
	{
		*prev_solu = new_solu / count_paths;
		return (1);
	}
	return (0);
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

