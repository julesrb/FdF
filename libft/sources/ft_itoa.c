/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:53:08 by jubernar          #+#    #+#             */
/*   Updated: 2022/12/16 10:53:09 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_len(int n)
{
	int		neg;
	int		len;

	len = 0;
	neg = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
		neg = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len + neg);
}

void	ft_itoa_reverse(int n, int len, char *ascii)
{
	if (n < 0)
	{
		ascii[0] = '-';
		if (n == -2147483648)
		{
			ascii[--len] = 8 + 48;
			n = -214748364;
		}
		n *= -1;
	}
	while (n != 0)
	{
		ascii[--len] = (n % 10) + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ascii;

	len = ft_itoa_len(n);
	ascii = (char *) malloc (len + 1);
	if (!ascii)
		return (NULL);
	if (n == 0)
		ascii[0] = 48;
	ascii[len] = 0;
	ft_itoa_reverse(n, len, ascii);
	return (ascii);
}
