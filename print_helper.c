/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:28:23 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/24 12:41:37 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_fast_path(t_path *paths, int count_ants, int path_val)
{
	int		i;
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

int			print_ant_move(t_path path, t_room *graph,
							int room, int *flag_space)
{
	if (*flag_space)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(path.roomnum_path[room].antnum);
	ft_putchar('-');
	ft_putstr(graph[path.roomnum_path[room].roomnum].name);
	*flag_space += 1;
	return (1);
}

int			make_pathstep(t_lemin **lemin, int path_val,
					int all_ants, int flag_space)
{
	int		i;
	int		moves;

	i = (*lemin)->paths[path_val].length - 1;
	moves = 0;
	while (i >= 0)
	{
		if (i == 0 &&
			is_fast_path((*lemin)->paths, (*lemin)->count_ants, path_val))
		{
			calc_first_step(lemin, path_val, i, all_ants);
			moves += print_ant_move((*lemin)->paths[path_val],
							(*lemin)->rooms, i, &flag_space);
		}
		else if (i && (*lemin)->paths[path_val].roomnum_path[i - 1].is_ant_here
			> 0 && ((*lemin)->paths[path_val].roomnum_path[i].is_ant_here == 0
			|| i == (*lemin)->paths[path_val].length - 1))
		{
			calc_step(lemin, path_val, i);
			moves += print_ant_move((*lemin)->paths[path_val],
							(*lemin)->rooms, i, &flag_space);
		}
		i--;
	}
	return (moves);
}

int			make_step(t_lemin *lemin, int count_paths, int all_ants)
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

void		print_solution(t_lemin *lemin, int count_ants, int count_rooms, int count_paths)
{
	int		count_moves;

	count_moves = 1;
	while (count_moves)
		count_moves = make_step(lemin, count_paths, count_ants);
}
