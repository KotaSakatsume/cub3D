/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:09:48 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/14 20:06:29 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	target;

	if (s == NULL)
		return (NULL);
	target = (unsigned char)c;
	str = (unsigned char *)s;
	while (n != 0)
	{
		*str = target;
		str++;
		n--;
	}
	return (s);
}
