/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:32:41 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 13:33:04 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(void)
{
	ft_putendl_fd("ERROR", 2);
	exit(-1);
}

int		main(int ac, char **av)
{
	t_lemin		*lemin;
	int			count_rooms;
	int			count_paths;

	lemin = validation();
	lemin->paths = get_first_path(lemin, get_count_rooms(lemin->list), 0);
	count_rooms = get_count_rooms(lemin->list);
	get_another_paths(&lemin, count_rooms, &count_paths);
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		print_paths(lemin->paths, lemin->rooms, count_paths);
	print_solution(lemin, lemin->count_ants, count_paths);
	free_all(lemin, count_rooms, count_paths);
	return (0);
}
