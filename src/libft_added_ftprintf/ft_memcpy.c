/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:54 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/14 20:13:30 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cpy;
	unsigned char	*tar;
	size_t			i;

	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
	cpy = (unsigned char *)dest;
	tar = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cpy[i] = tar[i];
		i++;
	}
	return (dest);
}
