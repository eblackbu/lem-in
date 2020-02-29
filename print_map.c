/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:41:05 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 13:41:36 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	if (room->bfs_lvl == 0)
		ft_putstr("##start\n");
	if (room->bfs_lvl == MAX_INT)
		ft_putstr("##end\n");
	ft_putstr(room->name);
	ft_putchar(' ');
	ft_putnbr(room->x);
	ft_putchar(' ');
	ft_putnbr(room->y);
	ft_putchar('\n');
}

void	print_links(t_room *rooms, int i)
{
	t_link		*tmp;

	tmp = rooms[i].links;
	while (tmp)
	{
		if (tmp->roomnum > i)
		{
			ft_putstr(rooms[i].name);
			ft_putchar('-');
			ft_putstr(rooms[tmp->roomnum].name);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

void	print_map(t_lemin *lemin, int count_rooms)
{
	t_roomlist	*tmp;
	int			i;

	tmp = lemin->list;
	ft_putnbr(lemin->count_ants);
	ft_putchar('\n');
	while (tmp)
	{
		print_room(tmp->room);
		tmp = tmp->next;
	}
	i = 0;
	while (i < count_rooms)
	{
		print_links(lemin->rooms, i);
		i++;
	}
	ft_putchar('\n');
}
