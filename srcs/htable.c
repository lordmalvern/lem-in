/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 19:35:14 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/12 12:53:25 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static t_list	*val_lstnew(t_room *f)
{
	t_room *val;
	t_list *out;
	int i;
	
	val = (t_room *)ft_memalloc(sizeof(t_room));
	val->num_ants = f->num_ants;
	val->x = f->x;
	val->y = f->y;
	val->r_name = ft_strdup(f->r_name);
	val->num_adj = f->num_adj;
	val->dist = INT_MAX;
	out->content = (void *)val;
	out->content_size = sizeof(t_room);
	out->next = NULL;
	return (out);
}

t_htable		*h_new(void)
{
	t_htable *out;

	out = (t_htable *)ft_memalloc(sizeof(t_htable));
	out->keys = (t_list **)ft_memalloc(H_SIZE * sizeof(t_list *));
	out->values = (t_list **)ft_memalloc(H_SIZE * sizeof(t_list *));
	
	return (out);
}

void			h_insert(t_htable *h, t_room *f)
{
	int i;
	t_list *key;
	t_list *val;

	i = h_index(h, f->r_name);
	key = ft_lstnew(f->r_name, ft_strlen(f->r_name) * sizeof(char));
	val = val_lstnew(f);
	if (h->keys[i] == NULL)
		h->keys[i] = key;
	else
		ft_lstadd(&h->keys[i], key);
	if (h->values[i] == NULL)
		h->values[i] = val;
	else
		ft_lstadd(&h->values[i], val);
	h->size++;
}

int				h_index(t_htable *h, char *k)
{
	int i;
	t_list *curr;

	i = (int) k % h->size;
	while (h->keys[i])
	{
		curr = h->keys[i];
		while (curr)
		{
			if (ft_strequ((char *)CUR(curr), k))
				return (i);
			curr = curr->next;
		}
		i = (i + 1) % h->size;
	}
	return (i);
}

void			h_del(t_htable **h)
{
	int i;

	i = -1;
	while (++i < (*h)->size)
	{
		ft_lstdel(&(*h)->keys[i], char_del);
		ft_lstdel(&(*h)->values[i], room_del);
		free((*h)->keys[i]);
		free((*h)->values[i]);
	}
	free((*h)->keys);
	free((*h)->values);
	free(*h);
}
