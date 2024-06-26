#include "fdf.h"

void	line_to_map_data(t_grid **grid, char *line, size_t col, size_t row)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		terminate("parse alloc error");
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

int	alloc_map(t_map *map)
{
	size_t		line;

	line = 0;
	map->grid = (t_grid **)malloc(map->row * sizeof(t_grid *));
	if (!map->grid)
	{
		return (0);
	}
	while (line < map->row)
	{
		map->grid[line] = (t_grid *)malloc(map->col * sizeof(t_grid));
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

int	parse_map(char *file_name, t_map *map)
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
		terminate("open failed");
	while (i < map->row)
	{	
		line = get_next_line(fd);
		if (!line)
			terminate("parse alloc error");
		line_to_map_data(map->grid, line, map->col, i);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
