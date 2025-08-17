/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:06:41 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/13 18:58:34 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*dest;

	if (lst == NULL)
		return (NULL);
	dest = lst;
	while (dest->next != NULL)
	{
		dest = dest->next;
	}
	return (dest);
}
