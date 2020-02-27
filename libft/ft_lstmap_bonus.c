/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:47:03 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/06 11:41:51 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s_list;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	s_list = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp && del)
		{
			ft_lstclear(&s_list, del);
			return (NULL);
		}
		ft_lstadd_back(&s_list, tmp);
		lst = lst->next;
	}
	return (s_list);
}
