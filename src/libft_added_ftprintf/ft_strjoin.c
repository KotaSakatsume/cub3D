/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:52:53 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/14 20:04:51 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1len;
	size_t	s2len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len + s2len == 0 || s1len > SIZE_MAX - s2len)
		return (ft_strdup(""));
	dest = malloc((s1len + s2len) * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, s1len + 1);
	ft_strlcpy(dest + s1len, s2, s2len + 1);
	return (dest);
}
