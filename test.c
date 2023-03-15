/* need to inc for open  */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/include/MLX42/MLX42.h"

#include "includes/fdf.h"
#include "libft/includes/libft.h"
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
	return (0);
}

int32_t	main (int argc, char *argv[])
{
	mlx_t*			mlx;
	mlx_image_t*	bckgnd;


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
	if (parse_map(argv[1]) == -1)
		return (0);

	mlx = mlx_init(WIDTH, HEIGHT, "fdf - MLX42", false);
	// include mlx errno and exit and resizing.
	bckgnd = mlx_new_image(mlx, WIDTH, HEIGHT);
	// include mlx errno and exit 

	//setting the background color
	ft_memset(bckgnd->pixels, 240, bckgnd->width * bckgnd->height * sizeof(int32_t));
	mlx_image_to_window(mlx, bckgnd, 0, 0);

	mlx_loop(mlx);
	// do i need mlx_delete_image ?
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// start codam minilib

// draw a line

// build my makefile 
/*
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build
cmake --build build -j4
*/

// Perror and sterror

// draw the parameter on screen.

// do i need my atohex ?



/* https://github.com/sungwoo-shin/ecole42-42cursus/tree/main/02-FdF */