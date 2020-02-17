#include "lem-in.h"
//TODO Беллман-Форд. Пройтись по всем комнатам, в каждой комнате смотреть каждую связь.
// Если связь есть, смотреть в переменную distance и обновлять, если distance больше чем путь до пред вершины + 1
t_path			*get_another_paths(t_lemin **lemin, int count_rooms)
{
	t_path		*new_path;
	int 		count_paths;

	count_paths = 1;
	new_path = get_new_path((*lemin)->rooms, count_paths);//Bellman-Ford
	while ((*lemin)->count_ants < count_paths && new_path)
	{
		/*
		 * TODO если новые пути удачнее для нашего количества муравьев, очищаем path и присваеваем указатель на new_path;
		 * 
		 */
	}
}
