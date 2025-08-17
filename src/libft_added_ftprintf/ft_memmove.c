/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:10:39 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/18 19:49:31 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rev_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cpy;
	unsigned char	*tar;

	if (dest == NULL || src == NULL)
		return (NULL);
	cpy = (unsigned char *)dest;
	tar = (unsigned char *)src;
	while (0 != n)
	{
		cpy[n - 1] = tar[n - 1];
		n--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL || src == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (dest > src)
		return (ft_rev_memcpy(dest, src, n));
	return (dest);
}
