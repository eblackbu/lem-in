/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:25:54 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 13:26:38 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_ifused_room(t_room *rooms, int room_from, int room_where)
{
	if (rooms[room_from].in_use && !rooms[room_where].in_use)
	{
		if (rooms[room_from].new_prev && rooms[room_from].new_prev->in_use)
			return (1);
		else
			return (0);
	}
	return (1);
}

void		set_distance(t_room **rooms, int i, int j, int weight)
{
	(*rooms)[j].dist = (*rooms)[i].dist + weight;
	if ((*rooms)[i].bfs_lvl != 0 && (*rooms)[i].bfs_lvl != MAX_INT)
		(*rooms)[i].new_next = &(*rooms)[j];
	if ((*rooms)[i].bfs_lvl != MAX_INT)
		(*rooms)[j].new_prev = &(*rooms)[i];
}

int			get_distance(t_room **rooms, int count_rooms)
{
	int		i;
	int		flag;
	t_link	*tmp;

	i = 0;
	flag = 0;
	while (i < count_rooms)
	{
		tmp = (*rooms)[i].links;
		while (tmp)
		{
			if ((*rooms)[tmp->roomnum].bfs_lvl != 0 && \
(*rooms)[i].dist != MAX_INT && (*rooms)[i].bfs_lvl != MAX_INT && \
(*rooms)[tmp->roomnum].dist > (*rooms)[i].dist + tmp->weight && \
check_ifused_room(*rooms, i, tmp->roomnum))
			{
				flag++;
				set_distance(rooms, i, tmp->roomnum, tmp->weight);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (flag);
}

t_path		*get_new_paths(t_room *rooms, int count_rooms, int count_paths)
{
	int		i;
	int		end;
	int		flag;
	t_path	*new_path;

	i = 0;
	new_path = NULL;
	end = get_end_room(rooms, count_rooms);
	flag = 1;
	while (flag && i < count_rooms + 1)
	{
		flag = get_distance(&rooms, count_rooms);
		i++;
	}
	if (i != count_rooms + 1 && rooms[end].dist != MAX_INT)
		new_path = del_overused_edges(rooms, count_rooms, count_paths);
	return (new_path);
}
