/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:42:29 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/29 13:43:20 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				is_number(char *line)
{
	char	*val;

	val = ft_itoa(ft_atoi(line));
	if (ft_strcmp(line, val) == 32)
	{
		ft_strdel(&val);
		return (1);
	}
	else
	{
		ft_strdel(&val);
		return (0);
	}
}

int				is_second_number(char *line)
{
	char	*val;

	val = ft_itoa(ft_atoi(line));
	if (!ft_strcmp(line, val))
	{
		ft_strdel(&val);
		return (1);
	}
	else
	{
		ft_strdel(&val);
		return (0);
	}
}

int				count_spaces(const char *roomline)
{
	int		n;
	int		count;

	n = 0;
	count = 0;
	while (roomline[n])
	{
		if (roomline[n] == ' ')
			count++;
		n++;
	}
	return (count);
}

int				check_roomline(char *roomline)
{
	if (roomline[0] == '#')
		return (1);
	if (count_spaces(roomline) == 2)
	{
		if (is_number(&ft_strchr(roomline, ' ')[1]) && \
		is_second_number(&ft_strrchr(roomline, ' ')[1]) && roomline[0] != 'L')
			return (1);
	}
	return (0);
}

int				get_start_end(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (START_ROOM);
	else if (!ft_strcmp(line, "##end"))
		return (END_ROOM);
	return (0);
}
