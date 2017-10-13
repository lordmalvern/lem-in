/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 14:36:17 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/13 10:43:54 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/ft_printf.h"
# include <limits.h>
# define CUR(a) ((a)->content)
# define NXT(a) (a)->next->content
# define ABS(a) ((a < 0) ? a * -1 : a);
# define H_SIZE 5000
# define Q_EMPTY(q) ((q)->start == (q)->end)
# define LEGAL(a) (a != '#' && a != 'L')

typedef struct	s_ant
{
	int		id;
	int		path_len;
	char	*room;
	char	**path;
}				t_ant;
typedef struct	s_room
{
	int				num_ants;
	int				x;
	int				y;
	int				dist;
	int				num_adj;
	char			*r_name;
	char			**adj;
}				t_room;
typedef struct	s_htable
{
	int		size;
	t_list	**keys;
	t_list	**values;
}				t_htable;
typedef struct	s_q
{
	char	**buf;
	size_t	start;
	size_t	end;
	size_t	size;
}				t_q;

t_htable		*h_new(void);
void			h_insert(t_htable **h, t_room *r);
int				h_index(t_htable *h, char *k);
void			h_del(t_htable **h);

void			char_del(void *content, size_t size);
void			room_del(void *content, size_t size);
void			ants_del(t_ant ***ants, int tot);

t_htable		*init_rooms(t_room **start, t_room **end, t_ant ***ants);
void			add_adj(char *cur, t_htable **out);

void			find_path(t_ant ***ants, t_htable **f, t_room **s, t_room **e);
void			next_room(t_ant **ant, t_room **s, t_room **n);
t_room			*get_room(t_htable **h, char *k);
t_ant			*init_ant(int i, t_room **s);

void			bfs(t_htable *h, char *s);
t_q				*new_q(void);
void			push(t_q *q, char *c);
char			*pop(t_q *q);

int				is_valid(char *c);
#endif
