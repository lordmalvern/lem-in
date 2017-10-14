/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:58:24 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 19:34:40 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	init_ends(t_room **r, t_htable **out, char *cur)
{
	char		**l;
	int			i;

	l = ft_strsplit(cur, ' ');
	i = 0;
	while (l[i] != NULL)
		i++;
	if (i == 3 && l[0] && l[1] && l[2] && !(*r)->r_name)
	{
		(*r)->r_name = ft_strdup(l[0]);
		(*r)->x = ft_atoi(l[1]);
		(*r)->y = ft_atoi(l[2]);
		(*r)->num_adj = 0;
		(*r)->adj = NULL;
		h_insert(out, *r);
	}
	while (i >= 0)
		free(l[i--]);
	free(l);
}

static void	init_room(t_htable **out, char *cur)
{
	char		**l;
	int			i;
	t_room		*r;

	l = ft_strsplit(cur, ' ');
	i = 0;
	while (l[i] != NULL)
		i++;
	if (i == 3 && l[0] && l[1] && l[2])
	{
		r = (t_room *)ft_memalloc(sizeof(t_room));
		r->r_name = ft_strdup(l[0]);
		r->x = ft_atoi(l[1]);
		r->y = ft_atoi(l[2]);
		r->num_adj = 0;
		r->adj = NULL;
		r->num_ants = 0;
		h_insert(out, r);
		ft_strdel(&(r->r_name));
		free(r);
	}
	while (--i >= 0)
		free(l[i]);
	free(l);
}

static void	build_ends(t_room **start, t_htable **out)
{
	char	*cur;

	if ((*start)->r_name)
		return ;
	get_next_line(0, &cur);
	ft_printf("%s\n", cur);
	if (LEGAL(cur[0]) && ft_strchr(cur, ' ') != NULL)
		init_ends(start, out, cur);
	ft_strdel(&cur);
}

static void	build(t_room **start, t_room **end, t_htable **out)
{
	char	*cur;

	cur = NULL;
	while (get_next_line(0, &cur) && is_valid(cur))
	{
		ft_printf("%s\n", cur);
		if ((ft_strequ(cur, "##start") && (*start)->r_name)
				|| (ft_strequ(cur, "##end") && (*end)->r_name))
			break ;
		else if (ft_strequ(cur, "##start"))
			build_ends(start, out);
		else if (ft_strequ(cur, "##end"))
			build_ends(end, out);
		else if (LEGAL(cur[0]) && ft_strchr(cur, ' ') != NULL)
			init_room(out, cur);
		else if (LEGAL(cur[0]) && ft_strchr(cur, '-') != NULL)
			add_adj(cur, out);
		ft_strdel(&cur);
	}
	ft_strdel(&cur);
}

t_htable	*init_rooms(t_room **start, t_room **end, t_ant ***ants)
{
	t_htable	*out;
	char		*cur;

	cur = NULL;
	if (get_next_line(0, &cur) <= 0 || !ft_isint(cur))
	{
		if (cur)
			ft_strdel(&cur);
		return (NULL);
	}
	out = h_new();
	(*start)->num_ants = ft_atoi(cur);
	*ants = (t_ant **)ft_memalloc((*start)->num_ants * sizeof(t_ant *));
	ft_strdel(&cur);
	build(start, end, &out);
	if (out->size > 0 && (*start)->r_name && (*end)->r_name)
	{
		(*start)->num_adj = (get_room(&out, (*start)->r_name))->num_adj;
		(*end)->num_adj = (get_room(&out, (*end)->r_name))->num_adj;
	}
	if (!(*start)->r_name || !(*end)->r_name
			|| (*start)->num_adj == 0 || (*end)->num_adj == 0)
		ants_del(ants, (*start)->num_ants);
	return (out);
}
