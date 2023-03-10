/* need to inc for open  */
#include <fcntl.h>

#include "libft/includes/libft.h"

#define MAP_SIZE_MAX 100

int parse_map(char *file_name)
{
	int	fd;
	int	row;
	char *line;
	char **map;

	row = 0;
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
	ft_printf("\n Map contains %i rows \n",row);
	map = (char**)malloc(row * sizeof(char*));
	if(!map)
		return (0);
	
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

	ft_split(line, " ");
	ft_printf("%s",line);
	//itoa
	//test if color
	//malloc 3d

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