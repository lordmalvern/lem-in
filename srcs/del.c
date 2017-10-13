/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 10:32:13 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 01:33:46 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void			char_del(void *content, size_t size)
{
	if (content)
		free(content);
	size = 0;
}

void			room_del(void *content, size_t size)
{
	int		i;
	t_room	*ptr;

	if (content)
	{
		ptr = (t_room *)content;
		ft_strdel(&ptr->r_name);
		i = -1;
		if (ptr->adj)
		{
			while (++i < ptr->num_adj)
				ft_strdel(&ptr->adj[i]);
		}
		free(ptr->adj);
		free(ptr);
	}
	size = 0;
}

void			ants_del(t_ant ***ants, int tot)
{
	int i;
	int j;

	i = -1;
	while (++i < tot)
	{
		j = -1;
		if ((ants[0][i])->path)
		{
			while (++j < (ants[0][i])->path_len)
				free((ants[0][i])->path[j]);
		}
		free(ants[0][i]->path);
		free(ants[0][i]);
	}
	free(ants[0]);
}
