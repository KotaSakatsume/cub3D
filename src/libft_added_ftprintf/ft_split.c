/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:57:06 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/18 23:02:50 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *str, size_t len)
{
	char	*sub;
	size_t	i;

	if (str == NULL)
		return (NULL);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = str[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static int	free_dest(char **dest, size_t num)
{
	size_t	i;

	i = 0;
	while (i <= num)
	{
		free(dest[i]);
	}
	return (-1);
}

static int	dests_pad(char **dest, const char *src, char c)
{
	size_t	len;
	size_t	count;
	char	*target;

	target = (char *)src;
	count = 0;
	while (*target != '\0')
	{
		while (*target == c)
			target++;
		if (*target != '\0')
		{
			len = 0;
			while (target[len] != c && target[len] != '\0')
				len++;
			dest[count] = ft_strndup(target, len);
			if (dest[count] == NULL)
				return (free_dest(dest, count));
			count++;
			target += len;
		}
	}
	return (count);
}

static size_t	count_words(const char *src, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[i] != '\0')
	{
		while (src[i] == c)
			i++;
		if (src[i] != '\0')
		{
			count++;
			while (src[i] != c && src[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**dest;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	dest = malloc((words + 1) * sizeof(char *));
	if (dest == NULL)
		return (NULL);
	if (dests_pad(dest, s, c) == -1)
	{
		free(dest);
		return (NULL);
	}
	dest[words] = NULL;
	return (dest);
}
