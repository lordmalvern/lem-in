/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 11:57:35 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 05:43:14 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void		step_next(t_ant **ant, t_htable **f, t_room **e)
{
	t_room *n;
	t_room *c;
	int i;

	i = -1;
	if (ft_strequ((*ant)->room, (*e)->r_name))
		return ;
	c = get_room(f, (*ant)->room);
	while (++i < c->num_adj)
	{
		n = get_room(f, c->adj[i]);
		if (n && ((n->num_ants >= 0 && ft_strequ((*e)->r_name, n->r_name))
				|| (n->num_ants == 0 && n->dist <= c->dist)))
			break ;
	}
	if (i < c->num_adj)
		next_room(ant, &c, &n);
}

void			find_path(t_ant ***ants, t_htable **f, t_room **s, t_room **e)
{
	int i;
	int tot_ants;
	int	p_path;
	t_room *end;

	tot_ants = (*s)->num_ants;
	end = get_room(f, (*e)->r_name);
	i = -1;
	while (++i < tot_ants)
		ants[0][i] = init_ant(i, s);
	bfs(*f, (*e)->r_name);
	while (end->num_ants < tot_ants)
	{
		i = -1;
		while (++i < tot_ants)
		{
			p_path = (ants[0][i])->path_len;
			step_next(&(ants[0][i]), f, e);
			if (p_path < (ants[0][i])->path_len)
				ft_printf("L%d-%s ", (ants[0][i])->id, (ants[0][i])->room);
		}
		ft_putstr("\b\n");
	}
	ants_del(ants, tot_ants);
}

void			next_room(t_ant **ant, t_room **c, t_room **n)
{
	char **n_path;
	int i;

	n_path = (char **)ft_memalloc(((*ant)->path_len + 1) * sizeof(char *));
	(*c)->num_ants--;
	(*ant)->room = (*n)->r_name;
	(*n)->num_ants++;
	i = -1;
	while (++i < (*ant)->path_len)
	{
		n_path[i] = ft_strdup((*ant)->path[i]);
		ft_strdel(&(*ant)->path[i]);
	}
	n_path[i] = ft_strdup((*n)->r_name);
	free((*ant)->path);
	(*ant)->path = n_path;
	(*ant)->path_len++;
}

t_room			*get_room(t_htable **h, char *k)
{
	int		i;
	t_list	*curr;
	t_room	*c;
	if (!k || !LEGAL(k[0]))
		return (NULL);
	i = h_index(*h, k);
	curr = (*h)->values[i];
	if (curr)
	{
		c = (t_room *)CUR(curr);
		while (curr && !ft_strequ(c->r_name, k))
		{
			curr = curr->next;
			c = (t_room *)CUR(curr);
		}
		return (CUR(curr));
	}
	return (NULL);
}

t_ant			*init_ant(int i, t_room **s)
{
	t_ant *out;
	out = (t_ant *)ft_memalloc(sizeof(t_ant));
	out->id = i + 1;
	out->room = (*s)->r_name;
	out->path_len = 1;
	out->path = (char **)ft_memalloc(sizeof(char *));
	out->path[0] = ft_strdup((*s)->r_name);
	return (out);
}
