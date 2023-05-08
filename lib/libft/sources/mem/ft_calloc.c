/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:59:03 by jubernar          #+#    #+#             */
/*   Updated: 2022/12/12 11:59:05 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	size_t	bits;
	char	*buffer;

	if (size == 0 || nmemb == 0)
	{
		buffer = malloc (0);
		return (buffer);
	}
	bits = nmemb * size;
	buffer = malloc (bits);
	if (buffer == NULL || nmemb == 0)
		return (NULL);
	i = 0;
	while (bits--)
	{
		buffer[i] = 0;
		i++;
	}
	return (buffer);
}
