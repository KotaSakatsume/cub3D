/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:20:13 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/13 16:55:26 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*dest_top;
	t_list	*dest_bef;

	dest_top = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		dest = ft_lstnew(f(lst->content));
		if (dest == NULL)
		{
			ft_lstclear(&dest_top, del);
			return (NULL);
		}
		if (dest_top == NULL)
			dest_top = dest;
		else
			dest_bef->next = dest;
		dest_bef = dest;
		lst = lst->next;
	}
	return (dest_top);
}
