/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_split(char **split)
{
	int	c;

	c = 0;
	while (split[c] != NULL)
	{
		free(split[c]);
		c++;
	}
	free(split[c]);
	free(split);
	return (0);
}

int	count_split(char **split)
{
	int	c;

	c = 0;
	while (split[c] != 0)
		c++;
	return (c);
}

int	count_map_colums(char *file_name, t_map *map)
{
	int		fd;
	char	**split;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		terminate("open error");
	line = get_next_line(fd);
	if (!line)
		terminate("parse alloc error");
	split = ft_split(line, ' ');
	if (!split)
		terminate("parse alloc error");
	map->col = count_split(split);
	free(line);
	free_split(split);
	map->col_c = ft_itoa(map->col);
	close(fd);
	return (0);
}

int	count_map_row(char *file_name, t_map *map)
{
	int		fd;
	char	*line;

	line = "init";
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		terminate("open error");
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			map->row++;
		free(line);
	}
	close(fd);
	map->row_c = ft_itoa(map->row);
	return (0);
}
