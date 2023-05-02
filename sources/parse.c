/* need to inc for open  */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fdf.h"

int count_split(char **split)
{
	int	c;

	c = 0;
	while (split[c] != 0)
		c++;
	return (c);
}

uint8_t	ft_atohex (char * str)
{
	uint8_t	a;
	uint8_t b;

	if (str[0] >= '0' && str[0] <= '9')
		a = str[0] - 48;
	if (str[0] >= 'a' && str[0] <= 'f')
		a = str[0] - 87;
	if (str[0] >= 'A' && str[0] <= 'F')
		a = str[0] - 55;
	if (str[1] >= '0' && str[1] <= '9')
		b = str[1] - 48;
	if (str[1] >= 'a' && str[1] <= 'f')
		b = str[1] - 87;
	if (str[1] >= 'A' && str[1] <= 'F')
		b = str[1] - 55;
	return ((a * 16) + b);
}

int	ft_ahextorgba (char * str)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	int	i;
	
	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (str[i] != 'x')
		i++;
	i++;
	r = ft_atohex(&str[i]);
	if (str[i + 2] != '\0')
	{
		g = ft_atohex(&str[i + 2]);
		if (str[i + 4] != '\0')
			b = ft_atohex(&str[i + 4]);
	}
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void	line_to_map_data(intersection_t **coordinate, char *line, size_t col, size_t row)
{
	char	**split;
	size_t		i;

	i = 0;
	split = ft_split(line, ' ');
	while (i < col)
	{
		//ft_printf("-%i",ft_atoi(split[i]));
		coordinate[row][i].height = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			coordinate[row][i].color = ft_ahextorgba(split[i]);
		else
			coordinate[row][i].color = 0xFFFFFFFF;
		//ft_printf("-%x", coordinate[row][i].color);
		i++;
	}
	// THink about implementing the colors management.
}

int	read_map(char *file_name, map_t* map)
{
	int		fd;
	char	**split;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	if (!(line = get_next_line(fd)))
		return (0);
	else
			map->row++;
	split = ft_split(line, ' ');
	map->col = count_split(split);
	free(line);
	//free the split
	ft_printf("\n Map contains %i columns \n", map->col);
	while (line)
	{
		if (!(line = get_next_line(fd)))
			return (0);
		else
			map->row++;
		free(line);
	}
	close(fd);
	ft_printf("\n Map contains %i rows \n",map->row);
	return (1);
}

int	alloc_map(map_t* map)
{
	size_t		line;

	line = 0;
	map->coordinate = (intersection_t**)malloc(map->row * sizeof(intersection_t*));
	if(!map->coordinate)
	{
		return (0);
	}
	while (line < map->row)
		{
			map->coordinate[line] = (intersection_t*)malloc(map->col * sizeof(intersection_t));
			if(!map->coordinate[line])
			{
				while (line-- > 0)
					free(map->coordinate[line]);
				free(map->coordinate);
				return (0);
			}
			line++;
		}
		return (1);
}

int	parse_map(char *file_name, map_t* map)
{
	int		fd;
	size_t		i;

	char	*line;

	i = 0;

	read_map(file_name, map);
	alloc_map(map);

	// NOW I NEED TO DISTRIBUTE THE DATA IN THE @D ARRAY WITH SPLIT
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	while (i < map->row)
	{	
		line = get_next_line(fd);
		line_to_map_data(map->coordinate, line, map->col, i);
		i++;
	}
	close(fd);
	return (0);
}
