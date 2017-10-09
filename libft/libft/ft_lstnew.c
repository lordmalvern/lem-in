/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 21:53:49 by bpuschel          #+#    #+#             */
/*   Updated: 2017/10/08 15:54:40 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*head;

	head = (t_list *)ft_memalloc(sizeof(t_list));
	if (head == NULL)
		return (NULL);
	head->content = NULL;
	head->content_size = 0;
	head->content = ft_memalloc(content_size * sizeof(void));
	if (content == NULL || head->content == NULL)
		return (head);
	else
	{
		ft_memcpy(head->content, content, content_size);
		head->content_size = content_size;
	}
	head->next = NULL;
	return (head);
}
