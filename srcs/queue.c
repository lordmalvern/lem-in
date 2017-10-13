/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 08:44:11 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 14:03:00 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_q				*new_q(void)
{
	t_q	*out;

	out = (t_q *)ft_memalloc(sizeof(t_q));
	out->size = 4;
	out->buf = (char **)ft_memalloc(out->size * sizeof(char *));
	out->start = 0;
	out->end = 0;
	return (out);
}

void			push(t_q *q, char *c)
{
	char	**new_buf;
	size_t	i;

	if (q->end >= q->size)
		q->end = 0;
	q->buf[q->end++] = ft_strdup(c);
	if (q->end == q->size)
	{
		new_buf = (char **)ft_memalloc(q->size * 2 * sizeof(char *));
		i = -1;
		while (++i < q->size)
		{
			new_buf[i] = ft_strdup(q->buf[i]);
			ft_strdel(&(q->buf[i]));
		}
		free(q->buf);
		q->buf = new_buf;
		q->size *= 2;
	}
}

char			*pop(t_q *q)
{
	char	*out;
	char	**new_buf;
	size_t	i;

	if (Q_EMPTY(q))
		return (NULL);
	out = ft_strdup(q->buf[q->start++]);
	ft_strdel(&(q->buf[q->start - 1]));
	if (q->start >= q->size)
	{
		q->start = 0;
		if (q->size >= H_SIZE / 2 && q->end < q->size / 2)
		{
			new_buf = (char **)ft_memalloc((q->size / 2) * sizeof(char *));
			i = -1;
			while (++i <= q->end)
			{
				new_buf[i] = ft_strdup(q->buf[i]);
				ft_strdel(&(q->buf[i]));
			}
			free(q->buf);
			q->buf = new_buf;
		}
	}
	return (out);
}
