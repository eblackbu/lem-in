#include <stdio.h>
#include "lem-in.h"

int		main()
{
	t_lemin		*lemin;
	t_path		**paths;

	paths = NULL;
	freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map", "r", stdin);
	lemin = validation();
	paths = get_paths(lemin->links, get_count_rooms(lemin->map));
	/*
	 * t_path paths = get_solution(lemin); Найти список всех нужных путей. Если 1 муравей, то дейкстра
	 * print_solution(lemin, paths);
	 * free_all(lemin, paths);
	 */
	return (0);
}

