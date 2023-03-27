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

void	line_to_map_data(intersection_t **geography, char *line, size_t col, size_t row)
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

int parse_map(char *file_name, map_t* map)
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

	map->geography = (intersection_t**)malloc(map->row * sizeof(intersection_t*));
	if(!map->geography)
		return (0);
	while (loc < map->row)
		{
			map->geography[loc] = (intersection_t*)malloc(map->col * sizeof(intersection_t));
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

void	text_info(mlx_t *mlx, char *argv, map_t *map)
{

	mlx_put_string(mlx, "NAME", 20, 25);
	mlx_put_string(mlx, ft_strchr(argv, '/'), 100, 25);
	mlx_put_string(mlx, "WIDTH", 20, 50);
	mlx_put_string(mlx, ft_itoa(map->col), 100, 50);
	mlx_put_string(mlx, "LENGHT", 20, 75);
	mlx_put_string(mlx, ft_itoa(map->row), 100, 75);
}

void	calculate_gradient_steps(int distancex, int color_a, int color_b , float RGBA_steps[4])
{
	(void)distancex;
	(void)color_a;
	(void)color_b;
	(void)RGBA_steps;
}

void draw_line_F_down(point_t point_a, point_t point_b, mlx_image_t *fdf)
{
	int	dx;
	int	dy;
	int	p;
	float RGBA_steps[4];

	dx = x1 - x;
	dy = y1 - y;

	p = 2 * dy - dx;
	ft_printf("distance fdown or gradient : %i\n", dx);
	calculate_gradient_steps(dx, color_a, color_b, &*RGBA_steps);
	while(x < x1)
	{
		mlx_put_pixel(fdf, x, y, color_a);
		mlx_put_pixel(fdf, x, y, color_b);
		if(p >= 0)
		{
			y++;
			p = p + 2 * dy - 2 * dx;
		}
		else
			p = p + 2 * dy;
	x++;
	}
}

void draw_line_F_up(int x, int y, int x1, int y1, mlx_image_t *fdf, int color_a, int color_b)
{
	int	distancex;
	int	distancey;
	int	p;

	distancex = x1 - x;
	distancey = y - y1;
	p = 2 * distancey - distancex;
	ft_printf("distance x or gradient : %i\n", distancex);
	while(x < x1)
	{
		mlx_put_pixel(fdf, x, y, color_a);
		mlx_put_pixel(fdf, x, y, color_b);
		if(p >= 0)
		{
			y--;
			p = p + 2 * distancey - 2 * distancex;
		}
		else
		{
			p = p + 2 * distancey;
		}
	x++;
	}
}

void draw_line_B_up(int x, int y, int x1, int y1, mlx_image_t *fdf, int color_a, int color_b)
{
	int	distancex;
	int	distancey;
	int	p;

	distancex = x - x1;
	distancey = y - y1;
	p = 2 * distancey - distancex;
	ft_printf("distance x or gradient : %i\n", distancex);
	while(x1 < x)
	{
		mlx_put_pixel(fdf, x, y, color_a);
		mlx_put_pixel(fdf, x, y, color_b);
		if(p >= 0)
		{
			y--;
			p = p + 2 * distancey - 2 * distancex;
		}
		else
		{
			p = p + 2 * distancey;
		}
	x--;
	}
}

void draw_line_B_down(int x, int y, int x1, int y1, mlx_image_t *fdf, int color_a, int color_b)
{
	int	dx;
	int	dy;
	int	p;

	dx = x - x1;
	dy = y1 - y;
	p = 2 * dy - dx;
	ft_printf("distance b down or gradient : %i\n", dx);
	while(x1 < x)
	{
		mlx_put_pixel(fdf, x, y, color_a);
		mlx_put_pixel(fdf, x, y, color_b);
		if(p >= 0)
		{
			y++;
			p = p + 2 * dy - 2 * dx;
		}
		else
			p = p + 2 * dy;
	x--;
	}
}

void draw_line(point_t point_a, point_t point_b, mlx_image_t *fdf)
{
	if (point_b.x >= point_a.x)
	{
		if (point_b.y >= point_a.y)
			draw_line_F_down(point_t point_a, point_t point_b, mlx_image_t *fdf);
		else
			draw_line_F_up(point_t point_a, point_t point_b, mlx_image_t *fdf);
	}
	else
	{
		if (point_b.y >= point_a.y)
			draw_line_B_down(point_t point_a, point_t point_b, mlx_image_t *fdf);
		else
			draw_line_B_up(point_t point_a, point_t point_b, mlx_image_t *fdf);
	}
}

int32_t	main (int argc, char *argv[])
{
	mlx_t*			mlx;
	mlx_image_t*	bckgnd;
	mlx_image_t*	fdf;
	map_t			map = {0, 0, 0};


	if (argc != 2)
		return (ft_printf("!! Incorrect number of arguments !!"));
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
		return (ft_printf("!! Wrong extension !!"));
	if (parse_map(argv[1], &map) == -1)
		return (0);

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	// include mlx errno and exit and resizing.
	bckgnd = mlx_new_image(mlx, WIDTH, HEIGHT);
	fdf = mlx_new_image(mlx, WIDTH, HEIGHT);
	// include mlx errno and exit 

	//setting the background color
	ft_memset(bckgnd->pixels, 50, bckgnd->width * bckgnd->height * sizeof(int32_t));
	mlx_image_to_window(mlx, bckgnd, 0, 0);

	point_t point_a;
	point_t point_b;

	point_a = {300, 300, 0xFF0000FF};
	point_b = {300, 300, 0xFFFFFFFF};
	draw_line(point_a, point_b, fdf);
	//draw_line(300, 300, 500, 200, fdf, 0xFF0000FF, 0x00FF00FF);
	//draw_line(300, 300, 50, 100, fdf, 0xFF0000FF, 0x0000FFFF);
	//draw_line(300, 300, 50, 600, fdf, 0xFF0000FF, 0xFFFF00FF);
	//draw_map(map, fdf);
	mlx_image_to_window(mlx, fdf, 0, 0);

	text_info(mlx, argv[1], &map);

	mlx_loop(mlx);
	// do i need mlx_delete_image ?
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


// gradient color line
// line in all directions
// draw full map 
// understand bresenham

// projectio 2d 3d

// Perror and sterror

// draw the parameter on screen.

// deal with colors. do i need my atohex ?



/* https://github.com/sungwoo-shin/ecole42-42cursus/tree/main/02-FdF */