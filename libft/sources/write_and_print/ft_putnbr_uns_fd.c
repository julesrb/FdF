/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_uns_fd(unsigned int nb, int fd)
{
	int	printed_char;

	printed_char = 0;
	if (nb >= 10)
	{
		printed_char += ft_putnbr_uns_fd(nb / 10, fd);
		printed_char += ft_putnbr_uns_fd(nb % 10, fd);
	}
	else
	{
		printed_char += ft_putchar_fd(nb + 48, fd);
	}
	return (printed_char);
}
