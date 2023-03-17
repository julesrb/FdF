/* need to inc for open  */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fdf.h"
#define WIDTH 1080
#define HEIGHT 720

int count_split(char **split)
{
	int	c;

	c = 0;
	while (split[c] != 0)
		c++;
	return (c);
}

void	line_to_map_data(t_intersection **geography, char *line, size_t col, size_t row)
{
	char	**split;
	size_t		i;

	i = 0;
	split = ft_split(line, ' ');
	while (i < col)
	{
		ft_printf("-%i",ft_atoi(split[i]));
		geography[row][i].height = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			geography[row][i].color = 0xff;
		i++;
	}
	// THink about implementing the colors management.
}

int parse_map(char *file_name, t_map* map)
{
	int		fd;
	size_t		i;
	size_t		loc;
	char	*line;
	char	**split;
	// geography[row][col];

	i = 0;
	loc = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("!! File reading problem !!");
		return (0);
	}
	line = get_next_line(fd);
	if (line)
			map->row++;
	split = ft_split(line, ' ');
	map->col = count_split(split);
	//free the split
	ft_printf("\n Map contains %i columns \n", map->col);
	while (line)
	{
		line = get_next_line(fd);
		//protection
		if (line)
			map->row++;
		
		// recheck the free function
		free(line);
	}
	close(fd);
	ft_printf("\n Map contains %i rows \n",map->row);

	// Re open and copy map. 

	map->geography = (t_intersection**)malloc(map->row * sizeof(t_intersection*));
	if(!map->geography)
		return (0);
	while (loc < map->row)
		{
			map->geography[loc] = (t_intersection*)malloc(map->col * sizeof(t_intersection));
			if(!map->geography[loc])
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
	while (i < map->row)
	{	
		line = get_next_line(fd);
		line_to_map_data(map->geography, line, map->col, i);
		ft_printf("\n");
		i++;
	}
	close(fd);
	return (0);
}

void	text_info(mlx_t *mlx, char *argv, t_map *map)
{

	mlx_put_string(mlx, "NAME", 20, 25);
	mlx_put_string(mlx, ft_strchr(argv, '/'), 100, 25);
	mlx_put_string(mlx, "WIDTH", 20, 50);
	mlx_put_string(mlx, ft_itoa(map->col), 100, 50);
	mlx_put_string(mlx, "LENGHT", 20, 75);
	mlx_put_string(mlx, ft_itoa(map->row), 100, 75);
}
int32_t	main (int argc, char *argv[])
{
	mlx_t*			mlx;
	mlx_image_t*	bckgnd;
	t_map			map = {0, 0, 0};


	if (argc != 2)
		return (ft_printf("!! Incorrect number of arguments !!"));
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
		return (ft_printf("!! Wrong extension !!"));
	if (parse_map(argv[1], &map) == -1)
		return (0);

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	// include mlx errno and exit and resizing.
	bckgnd = mlx_new_image(mlx, WIDTH, HEIGHT);
	// include mlx errno and exit 

	//setting the background color
	ft_memset(bckgnd->pixels, 50, bckgnd->width * bckgnd->height * sizeof(int32_t));
	mlx_image_to_window(mlx, bckgnd, 0, 0);

	text_info(mlx, argv[1], &map);

	mlx_loop(mlx);
	// do i need mlx_delete_image ?
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


// draw a line

// struct map 

// Perror and sterror

// draw the parameter on screen.

// deal with colors. do i need my atohex ?



/* https://github.com/sungwoo-shin/ecole42-42cursus/tree/main/02-FdF */