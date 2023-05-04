/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_to_map_data(grid_t **grid, char *line, size_t col, size_t row)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_split(line, ' ');
	while (i < col)
	{
		grid[row][i].height = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			grid[row][i].color = ft_ahextorgba(split[i]);
		else
			grid[row][i].color = 0xFFFFFFFF;
		i++;
	}
	free_split(split);
}

int	alloc_map(map_t *map)
{
	size_t		line;

	line = 0;
	map->grid = (grid_t **)malloc(map->row * sizeof(grid_t *));
	if (!map->grid)
	{
		return (0);
	}
	while (line < map->row)
	{
		map->grid[line] = (grid_t *)malloc(map->col * sizeof(grid_t));
		if (!map->grid[line])
		{
			while (line-- > 0)
				free(map->grid[line]);
			free(map->grid);
			return (0);
		}
		line++;
	}
	return (0);
}

int	parse_map(char *file_name, map_t *map)
{
	int		fd;
	size_t	i;
	char	*line;

	i = 0;
	count_map_colums(file_name, map);
	count_map_row(file_name, map);
	alloc_map(map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	while (i < map->row)
	{	
		line = get_next_line(fd);
		line_to_map_data(map->grid, line, map->col, i);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
