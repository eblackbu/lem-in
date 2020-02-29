/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_room.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:29:38 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 13:29:48 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*get_name(char *roomline)
{
	char	*name;
	int		n;

	n = 0;
	while (roomline[n] != ' ')
		n++;
	name = ft_strnew(n);
	ft_strncpy(name, roomline, n);
	return (name);
}

int			get_coordinate_x(char *roomline)
{
	int		n;

	n = 0;
	while (roomline[n] != ' ')
		n++;
	return (ft_atoi(&roomline[n + 1]));
}

int			get_coordinate_y(char *roomline)
{
	int		n;

	n = 0;
	while (roomline[n] != ' ')
		n++;
	n++;
	while (roomline[n] != ' ')
		n++;
	return (ft_atoi(&roomline[n + 1]));
}

t_room		*init_room(int num, char *roomline, int start_end)
{
	t_room	*new_room;

	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		exit(-1);
	new_room->number = num;
	new_room->name = get_name(roomline);
	new_room->x = get_coordinate_x(roomline);
	new_room->y = get_coordinate_y(roomline);
	if (start_end)
		new_room->bfs_lvl = (start_end == START_ROOM ? 0 : MAX_INT);
	else
		new_room->bfs_lvl = -1;
	return (new_room);
}
