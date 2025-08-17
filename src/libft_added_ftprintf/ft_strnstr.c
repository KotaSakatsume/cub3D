/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:46:33 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/18 22:49:07 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_size;
	size_t	big_size;
	size_t	compare_size;

	if (big == NULL || little == NULL)
		return (NULL);
	i = 0;
	little_size = ft_strlen(little);
	big_size = ft_strlen(big);
	if (little_size == 0)
		return ((char *)(big));
	if (little_size > len || little_size > big_size)
		return (NULL);
	if (big_size + 1 < len)
		compare_size = big_size - little_size;
	else
		compare_size = len - little_size + 1;
	while (i < compare_size)
	{
		if (ft_strncmp((big + i), little, little_size) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
