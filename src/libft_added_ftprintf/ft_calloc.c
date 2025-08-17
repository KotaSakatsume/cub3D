/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:30:32 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/14 20:05:50 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	size_t			i;

	if (nmemb == 0 || size == 0)
	{
		dest = malloc(1);
		if (dest != NULL)
			dest[0] = 0;
		return (dest);
	}
	if (SIZE_MAX / size < nmemb)
		return (NULL);
	dest = malloc(nmemb * (size));
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
