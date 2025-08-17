/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:06:10 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/07 23:06:21 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*check;

	if (lst == NULL)
		return (0);
	len = 1;
	check = lst->next;
	while (check != NULL)
	{
		len++;
		check = check->next;
	}
	return (len);
}
