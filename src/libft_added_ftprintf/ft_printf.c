/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:15:41 by mkuida            #+#    #+#             */
/*   Updated: 2024/12/03 23:21:19 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_and_printcall(char *str, va_list args, int words_count)
{
	if (ft_strnstr(str, "%c", 2))
		words_count = ft_printc(args, words_count);
	else if (ft_strnstr(str, "%s", 2))
		words_count = ft_prints(args, words_count);
	else if (ft_strnstr(str, "%p", 2))
		words_count = ft_printp(args, words_count);
	else if (ft_strnstr(str, "%d", 2) || ft_strnstr(str, "%i", 2))
		words_count = ft_printdi(args, words_count);
	else if (ft_strnstr(str, "%u", 2))
		words_count = ft_printu(args, words_count);
	else if (ft_strnstr(str, "%x", 2))
		words_count = ft_print_lowerx(args, words_count);
	else if (ft_strnstr(str, "%X", 2))
		words_count = ft_print_upperx(args, words_count);
	else if (ft_strnstr(str, "%%", 2))
		words_count = ft_printpercent(words_count);
	else
		words_count = -1;
	return (words_count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		words_count;
	char	*ptr;

	va_start(args, str);
	ptr = (char *)str;
	words_count = 0;
	while (*ptr != '\0')
	{
		if (*ptr == '%')
		{
			words_count = check_and_printcall(ptr, args, words_count);
			ptr = ptr + 2;
		}
		else
		{
			ft_putchar_fd(*ptr, STDOUT_FILENO);
			words_count++;
			ptr++;
		}
	}
	va_end(args);
	return (words_count);
}
