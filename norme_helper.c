/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblackbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:26:38 by eblackbu          #+#    #+#             */
/*   Updated: 2020/02/24 12:41:20 by eblackbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			calc_first_step(t_lemin **lemin, int path_val, int i, int all_ants)
{
	(*lemin)->count_ants--;
	(*lemin)->paths[path_val].roomnum_path[i].is_ant_here = 1;
	(*lemin)->paths[path_val].roomnum_path[i].antnum =
							all_ants - (*lemin)->count_ants;
	return (1);
}

int			calc_step(t_lemin **lemin, int path_val, int i)
{
	(*lemin)->paths[path_val].roomnum_path[i - 1].is_ant_here = 0;
	(*lemin)->paths[path_val].roomnum_path[i].is_ant_here = 1;
	(*lemin)->paths[path_val].roomnum_path[i].antnum =
						(*lemin)->paths[path_val].roomnum_path[i - 1].antnum;
	return (1);
}
