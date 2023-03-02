/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nb, int fd)
{
	int	printed_char;

	printed_char = 0;
	if (nb == -2147483648)
	{
		printed_char += ft_putchar_fd(-3 + 48, fd);
		printed_char += ft_putchar_fd(2 + 48, fd);
		printed_char += ft_putnbr_fd(147483648, fd);
	}
	else
	{
		if (nb < 0)
		{
			nb *= -1;
			printed_char += ft_putchar_fd(-3 + 48, fd);
		}
		if (nb >= 10)
		{
			printed_char += ft_putnbr_fd(nb / 10, fd);
			printed_char += ft_putnbr_fd(nb % 10, fd);
		}
		else
			printed_char += ft_putchar_fd(nb + 48, fd);
	}
	return (printed_char);
}
