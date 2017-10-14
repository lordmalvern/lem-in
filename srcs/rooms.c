/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 09:12:48 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 21:24:54 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		is_unique(char *c, t_htable *f)
{
	t_list *cur;
	int i;
	char **ent;
	int out;

	if (f->size == 0)
		return (1);
	ent = ft_strsplit(c, ' ');
	i = h_index(f, ent[0]);
	out = 1;
	cur = f->keys[i];
	while (cur != NULL && !ft_strequ(CUR(cur), ent[0]))
		cur = cur->next;
	if (cur && ft_strequ(CUR(cur), ent[0]))
		out = 0;
	free(ent[0]);
	free(ent[1]);
	free(ent[2]);
	free(ent);
	return (out);
}

int				is_valid(char *c, t_htable *f)
{
	int i;
	int spaces;
	int hyphens;

	i = -1;
	spaces = 0;
	hyphens = 0;
	if (c[0] == 'L')
		return (0);
	while (c[++i] != '\0')
	{
		spaces += (c[i] == ' ') ? 1 : 0;
		hyphens += (c[i] == '-') ? 1 : 0;
	}
	if (c[0] == '#')
		return (1);
	else if (spaces == 2 && hyphens == 0)
		return (is_unique(c, f));
	else if (hyphens == 1 && spaces == 0)
		return (1);
	return (0);
}

static void		adj_add(t_room **a, t_room **b)
{
	char	**a_new;
	int		i;

	a_new = ft_memalloc(((*a)->num_adj + 2) * sizeof(char *));
	i = -1;
	while (++i < (*a)->num_adj && (*a)->adj && (*a)->adj[i] != NULL)
	{
		a_new[i] = ft_strdup((*a)->adj[i]);
		ft_strdel(&((*a)->adj[i]));
	}
	a_new[i] = ft_strdup((*b)->r_name);
	ft_strdel(&((*a)->adj[i]));
	if ((*a)->adj)
		free((*a)->adj);
	(*a)->adj = a_new;
}

void			add_adj(char *cur, t_htable **out)
{
	char	**l;
	int		i;
	t_room	*a;
	t_room	*b;

	l = ft_strsplit(cur, '-');
	i = 0;
	while (l[i] != NULL)
		i++;
	if (i == 2 && l[0] && l[1])
	{
		a = get_room(out, l[0]);
		b = get_room(out, l[1]);
		if (a && b)
		{
			adj_add(&a, &b);
			adj_add(&b, &a);
			a->num_adj++;
			b->num_adj++;
		}
	}
	while (i >= 0)
		ft_strdel(&l[i--]);
	free(l);
}
