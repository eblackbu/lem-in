/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:34:46 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 13:36:11 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				is_dupl_path(t_path *paths, int count_paths)
{
	int		i;
	int		j;

	i = 1;
	while (i < count_paths)
	{
		j = 0;
		while (j < i)
		{
			if (paths[i].roomnum_path[0].roomnum == \
					paths[j].roomnum_path[0].roomnum)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				is_better_solution(t_path *paths, int count_paths, \
								int count_ants, int *prev_solu)
{
	int		i;
	int		new_solu;

	i = 0;
	new_solu = 0;
	while (i < count_paths)
	{
		new_solu += paths[i].length;
		i++;
	}
	new_solu += count_ants - i;
	new_solu = new_solu / count_paths;
	if (!is_dupl_path(paths, count_paths) && new_solu < *prev_solu)
	{
		*prev_solu = new_solu;
		return (1);
	}
	return (0);
}

void			sort_paths(t_path **paths, int count_paths)
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

void			print_roomname(char *name, int num)
{
	if (num == 0)
		ft_putstr(": ");
	else
		ft_putstr(" - ");
	ft_putstr(name);
}

void			print_paths(t_path *paths, t_room *rooms, int count_paths)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = 0;
	while (i < count_paths)
	{
		len += paths[i].length;
		j = 0;
		ft_putstr("Path №");
		ft_putnbr(i + 1);
		while (j < paths[i].length)
		{
			print_roomname(rooms[paths[i].roomnum_path[j].roomnum].name, j);
			j++;
		}
		i++;
		ft_putstr("\n\n");
	}
}
