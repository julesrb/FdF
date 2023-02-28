/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_for_n(char *temp)
{
	while (*temp)
	{
		if (*temp == '\n')
			return (1);
		temp++;
	}
	return (0);
}

char	*read_until_n(int fd, char *rest)
{
	char	*temp;
	char	*big_line;
	int		red;

	red = BUFFER_SIZE;
	big_line = rest;
	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	while (check_for_n(temp) != 1 && red == BUFFER_SIZE)
	{
		ft_bzero(temp, BUFFER_SIZE + 1);
		red = read(fd, temp, BUFFER_SIZE);
		if (red > 0)
			big_line = ft_strjoin(big_line, temp);
	}
	free(temp);
	if (ft_strlen(big_line) == 0 || red < 0)
	{
		free(rest);
		return (rest = NULL);
	}
	return (big_line);
}

char	*split_at_n(char *big_line)
{
	int		n;
	char	*rest;

	n = 0;
	while (big_line[n] != '\n' && big_line[n] != 0)
		n++;
	if (n + 1 < (int)ft_strlen(big_line))
	{
		rest = ft_strdup(&big_line[n + 1]);
		big_line[n + 1] = '\0';
	}
	else
		rest = NULL;
	return (rest);
}	

char	*get_next_line(int fd)
{
	char			*big_line;
	static char		*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = ft_calloc(1, 1 * sizeof(char));
		if (!rest)
			return (NULL);
	}
	big_line = read_until_n(fd, rest);
	if (big_line == NULL)
		return (rest = NULL);
	rest = split_at_n(big_line);
	return (big_line);
}

