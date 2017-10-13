/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:00:54 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 08:50:11 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lem-in.h"

static void		del_q(t_q **q)
{
	int i;

	i = -1;
	while (++i < (int)(*q)->size)
		free(((*q)->buf[i]));
	free((*q)->buf);
	free(*q);
}

static void		search(t_q **q, t_htable *h)
{
	t_room	*c;
	t_room	*n;
	int		d;
	int		i;
	char	*p;

	d = -1;
	while (!Q_EMPTY(*q))
	{
		i = -1;
		p = pop(*q);
		c = get_room(&h, p);
		c->dist = ++d;
		while (++i < c->num_adj)
		{
			n = get_room(&h, c->adj[i]);
			if (n && n->dist == INT_MAX)
			{
				n->dist = d + 1;
				push(*q, n->r_name);
			}
		}
		ft_strdel(&p);
	}
}

void			bfs(t_htable *h, char *s)
{
	t_q		*q;

	q = new_q();
	push(q, s);
	search(&q, h);
	del_q(&q);
}
