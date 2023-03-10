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

int parse_map(char *file_name)
{
	int		fd;
	int		row;
	int		col;
	char	*line;
	char	**split;
	t_intersection **map;
	// map[row][col];

	row = 0;
	col = 0;
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

	map = malloc(row * col * sizeof(t_intersection));
	if(!map)
		return (0);

	// NOW I NEED TO DISTRIBUTE THE DATA IN THE @D ARRAY WITH SPLIT
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	while (line)
	{	
		line = get_next_line(fd);
		if (line)
			row++;
	}
	close(fd);


	//itoa
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