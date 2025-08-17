/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:30:59 by mkuida            #+#    #+#             */
/*   Updated: 2024/12/05 11:58:40 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == '\f' || ch == '\n' || ch == '\r')
		return (1);
	else if (ch == '\t' || ch == '\v' || ch == ' ')
		return (1);
	else
		return (0);
}

static int	ft_issign(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == '-')
		return (-1);
	else if (ch == '+')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	long long	ans;
	int			sign;
	char		*ptr;

	ans = 0;
	ptr = (char *)nptr;
	if (nptr == NULL)
		return (0);
	while (ft_isspace(*ptr) == 1)
		ptr++;
	sign = ft_issign(*ptr);
	if (sign == 0)
		sign = 1;
	else
		ptr++;
	while (ft_isdigit(*ptr) == 1)
	{
		ans *= 10;
		ans += *ptr - '0';
		ptr++;
	}
	return ((int)(ans * sign));
}

	// if (ans * sign > INT_MAX)
	// 	return (INT_MAX);
	// if (ans * sign < INT_MIN)
	// 	return (INT_MIN);
