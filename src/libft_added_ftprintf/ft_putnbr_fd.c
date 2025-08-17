/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:38:16 by mkuida            #+#    #+#             */
/*   Updated: 2024/11/18 19:49:49 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_recursive(int n, int fd)
{
	char	printc;

	printc = (n % 10) + '0';
	if (n >= 10)
	{
		n = n / 10;
		print_recursive(n, fd);
	}
	write(fd, &printc, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	print_recursive(n, fd);
}
