/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:19:54 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/24 12:40:53 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*set_info_links(t_room *rooms, t_roomlist *list,
										int count_rooms)
{
	t_roomlist	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (i < count_rooms)
	{
		rooms[i].number = i;
		rooms[i].name = tmp->room->name;
		rooms[i].bfs_lvl = tmp->room->bfs_lvl;
		rooms[i].dist = rooms[i].bfs_lvl != 0 ? MAX_INT : 0;
		rooms[i].in_use = 0;
		rooms[i].links = NULL;
		rooms[i].prev = NULL;
		rooms[i].next = NULL;
		rooms[i].new_prev = NULL;
		rooms[i].new_next = NULL;
		i++;
		tmp = tmp->next;
	}
	return (rooms);
}

t_room			*init_links(int count_rooms, t_roomlist *map)
{
	t_room		*rooms;

	if (!(rooms = (t_room*)malloc(sizeof(t_room) * count_rooms)))
		error_exit();
	return (set_info_links(rooms, map, count_rooms));
}

int				set_link(int i, int j, t_room *rooms)
{
	rooms[i].links = add_new_link(rooms[i].links, 1, j);
	rooms[j].links = add_new_link(rooms[j].links, 1, i);
	return (1);
}

int				check_link(t_lemin **lemin, char *link, int count_rooms)
{
	int			i;
	int			j;
	size_t		len;

	i = 0;
	if (link[0] == '#' && ft_strcmp(link, "##start") \
		&& ft_strcmp(link, "##end"))
		return (1);
	while (i < count_rooms && ft_strcmp(link, (*lemin)->rooms[i].name) != '-')
		i++;
	if (i == count_rooms)
		error_exit();
	j = 0;
	len = ft_strlen((*lemin)->rooms[i].name) + 1;
	while (j < count_rooms && ft_strcmp(&link[len], (*lemin)->rooms[j].name))
		j++;
	if (j == count_rooms)
		error_exit();
	return (set_link(i, j, (*lemin)->rooms));
}
