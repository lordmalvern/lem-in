/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:58:24 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/12 12:09:17 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void		init_ends(t_room **r, t_htable **out, char *cur)
{
	char		**l;
	int			i;
	
	l = ft_strsplit(cur, ' ');
	i = 0;
	while (l[i] != NULL)
		i++;
	if (i == 3 && l[0] && l[1] && l[2])
	{
		(*r)->r_name = ft_strdup(l[0]);
		(*r)->x = ft_atoi(l[1]);
		(*r)->y = ft_atoi(l[2]);
		h_insert(*out, *r);
	}
	while (i >= 0)
		ft_strdel(&l[i--]);
	free(l);
}

static void		init_room(t_htable **out, char *cur)
{
	char		**l;
	int			i;
	t_room		*r;
	
	l = ft_strsplit(cur, ' ');
	i = 0;
	while (!ft_strequ(l[i], "\0"))
		i++;
	if (i == 3 && l[0] && l[1] && l[2])
	{
		r = (t_room *)ft_memalloc(sizeof(t_room));
		r->r_name = ft_strdup(l[0]);
		r->x = ft_atoi(l[1]);
		r->y = ft_atoi(l[2]);
		r->num_adj = 0;
		r->num_ants = 0;
		h_insert(*out, r);
		ft_strdel(&(r->r_name));
		free(r);
	}
	while (--i >= 0)
		ft_strdel(&l[i]);
	free(l);
}

t_htable		*init_rooms(t_room **start, t_room **end, t_ant ***ants)
{
	t_htable	*out;
	char		*cur;
	
	get_next_line(0, &cur);
	if (!ft_isint(cur))
		return (NULL);
	out = h_new();
	(*start)->num_ants = ft_atoi(cur);
	*ants = (t_ant **)ft_memalloc((*start)->num_ants * sizeof(t_ant *));
	while (get_next_line(0, &cur))
	{
		ft_printf("%s\n", cur);
		if (ft_strequ(cur, "##start"))
		{
			get_next_line(0, &cur);
			ft_printf("%s\n", cur);
			init_ends(start, &out, cur);
		}
		else if (ft_strequ(cur, "##end"))
		{
			get_next_line(0, &cur);
			ft_printf("%s\n", cur);
			init_ends(end, &out, cur);
		}
		else if (cur[0] != '#' && cur[0] != 'L'
				&& ft_strchr(cur, '-') == NULL)
			init_room(&out, cur);
		else if (cur[0] != '#' && cur[0] != 'L')
			add_adj(cur, &out);
	}
	(*start)->num_adj = (get_room(out, (*start)->r_name))->num_adj;
	(*end)->num_adj = (get_room(out, (*end)->r_name))->num_adj;
	return (out);
}

static void		adj_add(t_room **a, t_room **b)
{
	char	**a_new;
	char	**b_new;
	int		i;

	a_new = (char **)ft_memalloc(((*a)->num_adj + 1) * sizeof(char *));
	b_new = (char **)ft_memalloc(((*b)->num_adj + 1) * sizeof(char *));
	i = -1;
	while (++i < (*a)->num_adj)
	{
		a_new[i] = ft_strdup((*a)->adj[i]);
		ft_strdel(&((*a)->adj[i]));
	}
	a_new[i] = ft_strdup((*b)->r_name);
	free((*a)->adj);
	(*a)->adj = a_new;
	i = -1;
	while (++i < (*b)->num_adj)
	{
		b_new[i] = ft_strdup((*b)->adj[i]);
		ft_strdel(&((*b)->adj[i]));
	}
	b_new[i] = ft_strdup((*b)->r_name);
	free((*b)->adj);
	(*b)->adj = b_new;
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
		a = get_room(*out, l[0]);
		b = get_room(*out, l[1]);
		if (a && b)
		{
			adj_add(&a, &b);
			a->num_adj++;
			b->num_adj++;
		}
	}
	while (i >= 0)
		ft_strdel(&l[i--]);
	free(l);
}
