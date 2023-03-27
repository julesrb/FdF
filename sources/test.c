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

void	line_to_map_data(intersection_t **coordinate, char *line, size_t col, size_t row)
{
	char	**split;
	size_t		i;

	i = 0;
	split = ft_split(line, ' ');
	while (i < col)
	{
		ft_printf("-%i",ft_atoi(split[i]));
		coordinate[row][i].height = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			coordinate[row][i].color = 0xff;
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
	// coordinate[row][col];

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

	map->coordinate = (intersection_t**)malloc(map->row * sizeof(intersection_t*));
	if(!map->coordinate)
		return (0);
	while (loc < map->row)
		{
			map->coordinate[loc] = (intersection_t*)malloc(map->col * sizeof(intersection_t));
			if(!map->coordinate[loc])
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
		line_to_map_data(map->coordinate, line, map->col, i);
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

void	calculate_gradient_steps(int steps, int color_a, int color_b , float RGBA_steps[4])
{
	RGBA_steps[0] = (float)((uint8_t)(color_b >> 24) - (uint8_t)(color_a >> 24)) / (float)steps;
	RGBA_steps[1] = (float)((uint8_t)(color_b >> 16) - (uint8_t)(color_a >> 16)) / (float)steps;
	RGBA_steps[2] = (float)((uint8_t)(color_b >> 8) - (uint8_t)(color_a >> 8)) / (float)steps;
	RGBA_steps[3] = (float)((uint8_t)(color_b) - (uint8_t)(color_a)) / (float)steps;
}

int	calculate_gradient_color(int steps, int color_a, float RGBA_steps[4])
{
	return (((int)((uint8_t)(color_a >> 24) + steps * RGBA_steps[0]) & 0xFF) << 24 |
			((int)((uint8_t)(color_a >> 16) + steps * RGBA_steps[1]) & 0xFF) << 16 |
			((int)((uint8_t)(color_a >> 8) + steps * RGBA_steps[2]) & 0xFF) << 8 |
			((int)((uint8_t)(color_a >> 0) + steps * RGBA_steps[3]) & 0xFF) << 0);
}

void draw_line_F_down(point_t a, point_t b, mlx_image_t *fdf)
{
	int	dx;
	int	dy;
	int	p;
	int	i;
	float RGBA_steps[4];

	dx = b.x - a.x;
	dy = b.y - a.y;

	p = 2 * dy - dx;
	i = 0;
	ft_printf("distance fdown or gradient : %i\n", dx);

	calculate_gradient_steps(dx, a.color, b.color, &*RGBA_steps);
	while(a.x < b.x)
	{
		mlx_put_pixel(fdf, a.x, a.y, calculate_gradient_color(i, a.color, &*RGBA_steps));
		if(p >= 0)
		{
			a.y++;
			p = p + 2 * dy - 2 * dx;
		}
		else
			p = p + 2 * dy;
	a.x++;
	i++;
	}
}

void draw_line_F_up(point_t a, point_t b, mlx_image_t *fdf)
{
	int	dx;
	int	dy;
	int	p;
	int	i;
	float RGBA_steps[4];

	dx = b.x - a.x;
	dy = a.y - b.y;

	p = 2 * dy - dx;
	i = 0;
	ft_printf("distance fdown or gradient : %i\n", dx);

	calculate_gradient_steps(dx, a.color, b.color, &*RGBA_steps);
	while(a.x < b.x)
	{
		mlx_put_pixel(fdf, a.x, a.y, calculate_gradient_color(i, a.color, &*RGBA_steps));
		if(p >= 0)
		{
			a.y--;
			p = p + 2 * dy - 2 * dx;
		}
		else
			p = p + 2 * dy;
	a.x++;
	i++;
	}
}

void draw_line_B_up(point_t a, point_t b, mlx_image_t *fdf)
{
	int	dx;
	int	dy;
	int	p;
	int	i;
	float RGBA_steps[4];

	dx = a.x - b.x;
	dy = b.y - a.y;

	p = 2 * dy - dx;
	i = 0;
	ft_printf("distance fdown or gradient : %i\n", dx);

	calculate_gradient_steps(dx, a.color, b.color, &*RGBA_steps);
	while(b.x < a.x)
	{
		mlx_put_pixel(fdf, a.x, a.y, calculate_gradient_color(i, a.color, &*RGBA_steps));
		if(p >= 0)
		{
			a.y--;
			p = p + 2 * dy - 2 * dx;
		}
		else
			p = p + 2 * dy;
	a.x--;
	i++;
	}
}

void draw_line_B_down(point_t a, point_t b, mlx_image_t *fdf)
{
	int	dx;
	int	dy;
	int	p;
	int	i;
	float RGBA_steps[4];

	dx = a.x - b.x;
	dy = b.y - a.y;

	p = 2 * dy - dx;
	i = 0;
	ft_printf("distance fdown or gradient : %i\n", dx);

	calculate_gradient_steps(dx, a.color, b.color, &*RGBA_steps);
	while(b.x < a.x)
	{
		mlx_put_pixel(fdf, a.x, a.y, calculate_gradient_color(i, a.color, &*RGBA_steps));
		if(p >= 0)
		{
			a.y++;
			p = p + 2 * dy - 2 * dx;
		}
		else
			p = p + 2 * dy;
	a.x--;
	i++;
	}
}

void draw_line(point_t point_a, point_t point_b, mlx_image_t *fdf)
{
	if (point_b.x >= point_a.x)
	{
		if (point_b.y >= point_a.y)
			draw_line_F_down(point_a, point_b, fdf);
		else
			draw_line_F_up(point_a, point_b, fdf);
	}
	else
	{
		if (point_b.y >= point_a.y)
			draw_line_B_down(point_a, point_b, fdf);
		else
			draw_line_B_up(point_a, point_b, fdf);
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

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0xFF0000FF;
	point_b.x = 700;
	point_b.y = 500;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0x00FF00FF;
	point_b.x = 500;
	point_b.y = 200;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0x0000FFFF;
	point_b.x = 50;
	point_b.y = 100;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0xFFFF00FF;
	point_b.x = 50;
	point_b.y = 600;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);

	mlx_image_to_window(mlx, fdf, 0, 0);

	text_info(mlx, argv[1], &map);

	mlx_loop(mlx);
	// do i need mlx_delete_image ?
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


// gradient color line :)
// line in all directions :)

// read colors 
// draw full map 
// understand bresenham

// projectio 2d 3d

// Perror and sterror

// draw the parameter on screen.

// deal with colors. do i need my atohex ?



/* https://github.com/sungwoo-shin/ecole42-42cursus/tree/main/02-FdF */