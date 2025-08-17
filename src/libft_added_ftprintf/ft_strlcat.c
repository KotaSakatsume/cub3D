/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:01:29 by mkuida            #+#    #+#             */
/*   Updated: 2024/12/01 17:39:31 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ((size_t)(-1));
	while (s[i] != '\0' && i < n)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	total_size;
	size_t	i;

	if (dst == NULL || src == NULL)
		return ((size_t)(-1));
	i = 0;
	dst_size = ft_strnlen(dst, dstsize);
	src_size = ft_strnlen(src, dstsize);
	total_size = dst_size + src_size;
	if (dst_size >= dstsize)
		return (dstsize + src_size);
	while (dst_size + i < dstsize - 1 && i < src_size)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (total_size);
}
