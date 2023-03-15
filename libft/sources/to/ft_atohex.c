/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:55:26 by jubernar          #+#    #+#             */
/*   Updated: 2022/11/28 12:55:29 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atohex(const char *nptr)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '0')
		i++;
	if (nptr[i] == 'x')
		i++;
	while ((nptr[i] >= '0' && nptr[i] <= '9') || (nptr[i] >= 'a' && nptr[i] <= 'f'))
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (nbr * sign);	
}
