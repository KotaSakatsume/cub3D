/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cspp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:52:44 by mkuida            #+#    #+#             */
/*   Updated: 2024/12/03 23:21:38 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printc(va_list args, int words_counted)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, STDOUT_FILENO);
	return (words_counted + 1);
}

int	ft_prints(va_list args, int words_counted)
{
	char	*s;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	ft_putstr_fd(s, STDOUT_FILENO);
	return (words_counted + (int)ft_strlen(s));
}

static int	printp_recursive(uintptr_t u, int words_counted)
{
	char		printc;
	const char	*charset = "0123456789abcdef";

	printc = charset[u % 16];
	if (u >= 16)
	{
		u = u / 16;
		words_counted = printp_recursive(u, words_counted);
	}
	write(1, &printc, 1);
	return (words_counted + 1);
}

int	ft_printp(va_list args, int words_counted)
{
	int			count_words;
	uintptr_t	address;

	count_words = 0;
	address = va_arg(args, uintptr_t);
	if (address == 0)
	{
		ft_putstr_fd("(nil)", STDOUT_FILENO);
		return (words_counted + 5);
	}
	ft_putstr_fd("0x", STDOUT_FILENO);
	count_words = printp_recursive(address, count_words);
	return (count_words + words_counted + 2);
}

int	ft_printpercent(int words_counted)
{
	ft_putchar_fd('%', STDOUT_FILENO);
	return (words_counted + 1);
}
