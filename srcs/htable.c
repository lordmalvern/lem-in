/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 19:35:14 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 14:54:17 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_list	*val_lstnew(t_room *f)
{
	t_room *val;
	t_list *out;
	
	val = (t_room *)ft_memalloc(sizeof(t_room));
	out = (t_list *)ft_memalloc(sizeof(t_list));
	val->num_ants = f->num_ants;
	val->x = f->x;
	val->y = f->y;
	val->r_name = ft_strdup(f->r_name);
	val->num_adj = f->num_adj;
	val->dist = INT_MAX;
	out->content = (void *)val;
	out->content_size = sizeof(t_room);
	out->content_size += (ft_strlen(f->r_name) + 1) * sizeof(char);
	out->next = NULL;
	return (out);
}

t_htable		*h_new(void)
{
	t_htable	*out;
	int			i;

	out = (t_htable *)ft_memalloc(sizeof(t_htable));
	out->keys = (t_list **)ft_memalloc(H_SIZE * sizeof(t_list *));
	out->values = (t_list **)ft_memalloc(H_SIZE * sizeof(t_list *));
	i = -1;
	while (++i < H_SIZE)
	{
		out->keys[i] = NULL;
		out->values[i] = NULL;
	}
	return (out);
}

void			h_insert(t_htable **h, t_room *f)
{
	int		i;
	t_list	*key;
	t_list	*val;
	t_list	*curr;

	i = h_index(*h, f->r_name);
	curr = (*h)->keys[i];
	while (curr && !ft_strequ(((char *)CUR(curr)), f->r_name))
		curr = curr->next;
	if (!curr)
	{
		key = ft_lstnew((f->r_name), ft_strlen(f->r_name) * sizeof(char) + 1);
		val = val_lstnew(f);
		if ((*h)->keys[i] == NULL)
			(*h)->keys[i] = key;
		else
			ft_lstadd(&((*h)->keys[i]), key);
		if ((*h)->values[i] == NULL)
			(*h)->values[i] = val;
		else
			ft_lstadd(&((*h)->values[i]), val);
		(*h)->size++;
	}
}

int				h_index(t_htable *h, char *k)
{
	int		i;
	int		j;
	t_list	*curr;

	i = 0;
	j = -1;
	while (k[++j] != '\0')
		i += k[j];
	i %= H_SIZE;
	while (h->keys[i])
	{
		curr = h->keys[i];
		while (curr)
		{
			if (ft_strequ((char *)CUR(curr), k))
				return (i);
			curr = curr->next;
		}
		i = (i + 1) % H_SIZE;
	}
	return (i);
}

void			h_del(t_htable **h)
{
	int		i;
	t_list	*k;
	t_list	*v;

	i = -1;
	if (*h)
	{
		while (++i < H_SIZE)
		{
			k = (*h)->keys[i];
			v = (*h)->values[i];
			ft_lstdel(&k, char_del);
			ft_lstdel(&v, room_del);
			free(k);
			free(v);
		}
		free((*h)->keys);
		free((*h)->values);
		free(*h);
	}
}
