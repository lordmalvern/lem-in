/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 00:22:42 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 13:53:43 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(void)
{
	t_htable	*farm;
	t_room		*start;
	t_room		*end;
	t_ant		**ants;

	start = (t_room *)ft_memalloc(sizeof(t_room));
	end = (t_room *)ft_memalloc(sizeof(t_room));
	ants = NULL;
	farm = init_rooms(&start, &end, &ants);
	if (!ants)
		ft_printf("Error: No ants or empty file\n");
	else if (farm->size == 0)
		ft_printf("Error: No rooms\n");
	else if (!start->r_name || !end->r_name)
		ft_printf("Error: No start or end\n");
	else if (start->num_adj == 0 || end->num_adj == 0)
		ft_printf("Error: No valid path\n");
	else
		find_path(&ants, &farm, &start, &end);
	room_del(start, 0);
	room_del(end, 0);
	h_del(&farm);
	return (0);
}
