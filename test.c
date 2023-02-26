#include <stdio.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

#define MAP_SIZE_MAX 100


parse_map(char file_name)
{
	int	fd;
	int	l;
	char *line;
	char *map[MAP_SIZE_MAX];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		{
			printf("!! File reading problem !!");
			return (0);
		}
	while (line)
	{	
		line = get_next_line(fd);
		l++
		map
		//itoa
		//malloc
	}
}

int	main (int argc, char argv[])
{
	if (argc != 1)
	{
		printf("!! Incorrect number of arguments !!");
		return (0);
	}

	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
	{
		printf("!! wrong extension !!");
		return (0);
	}

	parse_map(argv[1]);

	//save map 


	return (0);
}