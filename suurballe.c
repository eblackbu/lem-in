#include "lem-in.h"

t_path			*set_new_paths(t_room *rooms, int count_rooms, \
								int count_paths, int end_room)
{
	t_path		*paths;
	t_link		*tmp;
	int			i;


	i = 0;
	if (!(paths = (t_path*)malloc(sizeof(t_path) * (count_paths + 1))))
		exit(-1);
	tmp = rooms[end_room].links;
	while (tmp)
	{
		if (tmp->weight == -1)
		{
			paths[i].length = get_len_suur(rooms, tmp->roomnum);
			paths[i].roomnum_path = get_roomnumpath_suur(rooms, count_rooms,
					tmp->roomnum, paths[i].length);
			i++;
		}
		tmp = tmp->next;
	}
	return (paths);
}

t_room			*set_neg_weight(t_room *rooms, int next_room, int prev_room)
{
	t_link		*tmp;

	tmp = rooms[next_room].links;
	while (tmp->roomnum != prev_room)
		tmp = tmp->next;
	if (!tmp)
		exit(-1);
	tmp->weight = -1;
	rooms = del_link(rooms, prev_room, next_room);
	return (rooms);
}

t_path 			*del_overused_edges(t_room *rooms, int count_rooms, int count_paths)
{
	int			end_room;
	int			tmp_room;
	int 		last_room;

	end_room = get_end_room(rooms, count_rooms);
	last_room = rooms[end_room].new_prev->number;
	rooms = set_neg_weight(rooms, end_room, last_room);
	while (rooms[last_room].bfs_lvl != 0)
	{
		tmp_room = last_room;
		last_room = rooms[tmp_room].new_prev->number;
		if (get_weight_link(rooms, last_room, tmp_room) != -1)
		{
			rooms = set_neg_weight(rooms, tmp_room, last_room);
			rooms[tmp_room].prev = rooms[tmp_room].new_prev;
			rooms[tmp_room].next = rooms[tmp_room].new_next;
		}
		else
			rooms = del_link(rooms, last_room, tmp_room);
	}
	return (set_new_paths(rooms, count_rooms, count_paths, end_room));
}

void			get_another_paths(t_lemin **lemin, int count_rooms, int *count_paths)
{
	t_path		*new_path;
	int 		solu_length;
	int 		tmp_count_paths;

	*count_paths = 1;
	tmp_count_paths = 1;
	solu_length = (*lemin)->paths[0].length + (*lemin)->count_ants - 1;
	new_path = get_new_paths((*lemin)->rooms, count_rooms, tmp_count_paths);
	while ((int)(*lemin)->count_ants > tmp_count_paths && new_path)
	{
		tmp_count_paths++;
		if (is_better_solution(new_path, tmp_count_paths, (*lemin)->count_ants, &solu_length))//TODO norme
		{
			del_all_paths((*lemin)->paths, *count_paths);
			(*lemin)->paths = new_path;
			*count_paths = tmp_count_paths;
		}
		else
			del_all_paths(new_path, tmp_count_paths);
		(*lemin)->rooms = set_null_distance((*lemin)->rooms, count_rooms);
		new_path = get_new_paths((*lemin)->rooms, count_rooms, tmp_count_paths);
	}
	sort_paths(&(*lemin)->paths, *count_paths);
}
