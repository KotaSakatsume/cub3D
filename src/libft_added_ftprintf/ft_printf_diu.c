/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:51:15 by mkuida            #+#    #+#             */
/*   Updated: 2024/12/03 23:21:45 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printdi_recursive(int d, int words_counted)
{
	char	printc;

	printc = (d % 10) + '0';
	if (d >= 10)
	{
		d = d / 10;
		words_counted = printdi_recursive(d, words_counted);
	}
	write(1, &printc, 1);
	return (words_counted + 1);
}

int	ft_printdi(va_list args, int words_counted)
{
	int	d;
	int	count_words;

	d = va_arg(args, int);
	count_words = 0;
	if (d == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (words_counted + 11);
	}
	if (d < 0)
	{
		write(1, "-", 1);
		d *= -1;
		count_words++;
	}
	count_words = printdi_recursive(d, count_words);
	return (words_counted + count_words);
}

static int	printu_recursive(unsigned int u, int words_counted)
{
	char	printc;

	printc = (u % 10) + '0';
	if (u >= 10)
	{
		u = u / 10;
		words_counted = printdi_recursive(u, words_counted);
	}
	write(1, &printc, 1);
	return (words_counted + 1);
}

int	ft_printu(va_list args, int words_counted)
{
	int				count_words;
	unsigned int	u;

	count_words = 0;
	u = va_arg(args, unsigned int);
	count_words = printu_recursive(u, count_words);
	return (words_counted + count_words);
}
