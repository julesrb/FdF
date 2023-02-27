/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:05:17 by jubernar          #+#    #+#             */
/*   Updated: 2022/12/12 15:05:17 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	if (s == NULL)
	{
		c += ft_putstr_fd("(null)", 1);
		return (c);
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
		c++;
	}
	write(fd, "\n", 1);
	return (c);
}
