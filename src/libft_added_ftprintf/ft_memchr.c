/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:08:12 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/14 20:02:55 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	target;
	size_t			i;

	if (s == NULL)
		return (NULL);
	dest = (unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (n > i)
	{
		if (dest[i] == target)
			return ((void *)(dest + i));
		i++;
	}
	return (NULL);
}
