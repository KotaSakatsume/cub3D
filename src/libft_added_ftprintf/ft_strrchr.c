/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:15:10 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/14 20:05:14 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	target;
	size_t			len;

	if (s == NULL)
		return (NULL);
	target = (unsigned int)c;
	len = ft_strlen(s);
	if (target == '\0')
		return ((char *)(s + len));
	while (len != 0)
	{
		if (s[len - 1] == target)
			return ((char *)(s + len - 1));
		len--;
	}
	return (NULL);
}
