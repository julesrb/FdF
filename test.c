/* need to inc for open  */
#include <fcntl.h>

#include "includes/fdf.h"
#include "libft/includes/libft.h"

int count_split(char **split)
{
	int	c;

	c = 0;
	while (split[c] != 0)
		c++;
	return (c);

}

void	line_to_map_data(t_intersection **map, char *line, size_t col, size_t row)
{
	char	**split;
	size_t		i;

	i = 0;
	split = ft_split(line, ' ');
	while (i < col)
	{
		ft_printf("-%i",ft_atoi(split[i]));
		map[row][i].height = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			map[row][i].color = 0xff;
		i++;
	}
	// THink about implementing the colors management.
}

int parse_map(char *file_name)
{
	int		fd;
	size_t		i;
	size_t		loc;
	size_t		row;
	size_t		col;
	char	*line;
	char	**split;
	t_intersection **map;
	// map[row][col];

	i = 0;
	row = 0;
	col = 0;
	loc = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	line = get_next_line(fd);
	if (line)
			row++;
	split = ft_split(line, ' ');
	col = count_split(split);
	//free the split
	ft_printf("\n Map contains %i columns \n",col);
	while (line)
	{
		line = get_next_line(fd);
		//protection
		if (line)
			row++;
		
		// recheck the free function
		free(line);
	}
	close(fd);
	ft_printf("\n Map contains %i rows \n",row);

	// Re open and copy map. 

	map = (t_intersection**)malloc(row * sizeof(t_intersection*));
	if(!map)
		return (0);
	while (loc < row)
		{
			map[loc] = (t_intersection*)malloc(col * sizeof(t_intersection));
			if(!map[loc])
				return (0);
			loc++;
		}

	// NOW I NEED TO DISTRIBUTE THE DATA IN THE @D ARRAY WITH SPLIT
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	while (i < row)
	{	
		line = get_next_line(fd);
		line_to_map_data(map, line, col, i);
		ft_printf("\n");
		i++;
	}
	close(fd);


	//atoi
	//test if color
	//malloc 3d
	return (0);
}

int	main (int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_printf("!! Incorrect number of arguments !!");
		return (0);
	}
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
	{
		ft_printf("!! wrong extension !!");
		return (0);
	}
	if (parse_map(argv[1]) == 0)
		return (0);

	//save map 


	return (0);
}


/* https://github.com/sungwoo-shin/ecole42-42cursus/tree/main/02-FdF */