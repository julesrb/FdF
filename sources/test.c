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

	mlx_put_string(mlx, "CONTROL", 20, 600);
	mlx_put_string(mlx, "Zoom in:  I", 20, 625);
	mlx_put_string(mlx, "Zoom out: O", 20, 650);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	fdf_t	*fdf;
	fdf = (fdf_t*)param;

	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
	{
		ft_printf("zoom In\n");
		fdf->zoom = fdf->zoom * 1.05;
		
	}
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		ft_printf("zoom Out\n");
		fdf->zoom = fdf->zoom * 0.95;

		
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		ft_printf("Top view\n");
		fdf->top = 1;
		fdf->iso = 0;
		
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		ft_printf("Iso view\n");
		fdf->iso = 1;
		fdf->top = 0;
	}
	draw_map(fdf);
	(void)param;
}

fdf_t	*fdf_init(char* name)
{
	fdf_t			*fdf;
	fdf = ft_calloc(1, sizeof(fdf_t));
	fdf->name = ft_strdup(name);
	fdf->map = ft_calloc(1, sizeof(map_t));

	fdf->top = 1;
	fdf->zoom = 1;

	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	// include mlx errno and exit and resizing.

	fdf->img_bck = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img_fdf = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	// include mlx errno and exit 

	return (fdf);
}

int32_t	main (int argc, char *argv[])
{
	fdf_t			*fdf;
	//mlx_image_t*	bckgnd;
	//mlx_image_t*	fdf;
	//fdf.env = {0, 1, 0, 1};


	if (argc != 2)
		return (ft_printf("!! Incorrect number of arguments !!"));
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
		return (ft_printf("!! Wrong extension !!"));

	fdf = fdf_init(argv[1]);
	if (parse_map(argv[1], fdf->map) == -1)
		return (0);



	//setting the background color
	ft_memset(fdf->img_bck->pixels, 50, fdf->img_bck->width * fdf->img_bck->height * sizeof(int32_t));
	mlx_image_to_window(fdf->mlx, fdf->img_bck, 0, 0);

	draw_map(fdf);



	//text_info(fdf.mlx, argv[1], &fdf.map);
	mlx_key_hook(fdf->mlx, &my_keyhook, &fdf);
	mlx_loop(fdf->mlx);
	// do i need mlx_delete_image ?
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}

// Center the 2d map
// How to handle the value that are outside of reach 2d
// center the iso map 

// Perror and sterror

// draw the parameter on screen.


/* https://github.com/sungwoo-shin/ecole42-42cursus/tree/main/02-FdF */

/* 	point_t point_a;
	point_t point_b;

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0xFF0000FF;
	point_b.x = 300;
	point_b.y = 600;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);
		point_a.x = 300;
		point_a.y = 300;
		point_a.color = 0xFF0000FF;
		point_b.x = 302;
		point_b.y = 600;
		point_b.color = 0xFFFFFFFF;
		draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0x00FF00FF;
	point_b.x = 600;
	point_b.y = 600;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0x0000FFFF;
	point_b.x = 600;
	point_b.y = 300;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);
		point_a.x = 300;
		point_a.y = 300;
		point_a.color = 0x0000FFFF;
		point_b.x = 600;
		point_b.y = 302;
		point_b.color = 0xFFFFFFFF;
		draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0x0000FFFF;
	point_b.x = 600;
	point_b.y = 200;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf);

	point_a.x = 300;
	point_a.y = 300;
	point_a.color = 0xFF00FFFF;
	point_b.x = 500;
	point_b.y = 100;
	point_b.color = 0xFFFFFFFF;
	draw_line(point_a, point_b, fdf); */