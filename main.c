#include <stdio.h>
#include "lem-in.h"

int		main()
{
	t_lemin		*lemin;

	freopen("/home/eblackbu/CLionProjects/lem-in/cmake-build-debug/test_map", "r", stdin);
	lemin = validation();

	/*
	 * t_path paths = get_solution(lemin); Найти список всех нужных путей. Если 1 муравей, то дейкстра
	 * print_solution(lemin, paths);
	 * free_all(lemin, paths);
	 */
	return (0);
}

