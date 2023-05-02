/* need to inc for open  */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fdf.h"
#define WIDTH 1080
#define HEIGHT 720

void	calc_gradient_steps(int i, int cl_a, int cl_b, float rgba[4])
{
	rgba[0] = (float)((uint8_t)(cl_b >> 24) - (uint8_t)(cl_a >> 24)) / (float)i;
	rgba[1] = (float)((uint8_t)(cl_b >> 16) - (uint8_t)(cl_a >> 16)) / (float)i;
	rgba[2] = (float)((uint8_t)(cl_b >> 8) - (uint8_t)(cl_a >> 8)) / (float)i;
	rgba[3] = (float)((uint8_t)(cl_b) - (uint8_t)(cl_a)) / (float)i;
}

int	calc_gradient_color(int steps, int cl_a, float rgba[4])
{
	return (((int)((uint8_t)(cl_a >> 24) + steps * rgba[0]) & 0xFF) << 24 |
			((int)((uint8_t)(cl_a >> 16) + steps * rgba[1]) & 0xFF) << 16 |
			((int)((uint8_t)(cl_a >> 8) + steps * rgba[2]) & 0xFF) << 8 |
			((int)((uint8_t)(cl_a >> 0) + steps * rgba[3]) & 0xFF) << 0);
}

// Reduce code with math absolute values 

// do the switch before sending to functions

// fix the color pick on the grid 		
void	draw_line_down_x_long(point_t a, point_t b, int *dist, mlx_image_t *fdf)
{
	float	f;
	int		i;
	float	rgba[4];

	i = 0;
	f = dist[0] / 2;
	calc_gradient_steps(dist[0], a.color, b.color, &*rgba);
	while (a.x < b.x)
	{
		mlx_put_pixel(fdf, a.x, a.y, calc_gradient_color(i, a.color, &*rgba));
		f = f - dist[1];
		if (f < 0)
		{
			a.y++;
			f = f + dist[0];
		}
		a.x++;
		i++;
	}
}

void	draw_line_down_y_long(point_t a, point_t b, int *dist, mlx_image_t *fdf)
{
	float	f;
	int		i;
	float	rgba[4];

	i = 0;
	f = dist[1] / 2;
	calc_gradient_steps(dist[1], a.color, b.color, &*rgba);
	while (a.y < b.y)
	{
		mlx_put_pixel(fdf, a.x, a.y, calc_gradient_color(i, a.color, &*rgba));
		f = f - dist[0];
		if (f < 0)
		{
			a.x++;
			f = f + dist[1];
		}
		a.y++;
		i++;
	}
}

void	draw_line_down(point_t a, point_t b, mlx_image_t *fdf)
{
	int		dx;
	int		dy;
	int		dist[2];

	dx = b.x - a.x;
	dy = b.y - a.y;
	dist[0] = dx;
	dist[1] = dy;
	if (dx > dy)
		draw_line_down_x_long(a, b, dist, fdf);
	else
		draw_line_down_y_long(a, b, dist, fdf);
}

void draw_line_up_x_long(point_t a, point_t b, int *dist, mlx_image_t *fdf)
{
	float	f;
	int		i;
	float	rgba[4];

	i = 0;
	f = dist[0] / 2;

	calc_gradient_steps(dist[0], a.color, b.color, &*rgba);
	while (a.x < b.x)
	{
		mlx_put_pixel(fdf, a.x, a.y, calc_gradient_color(i, a.color, &*rgba));
		f = f - dist[1];
		if (f < 0)
		{
			a.y--;
			f = f + dist[0];
		}
		a.x++;
		i++;
	}
}

void	draw_line_up_y_long(point_t a, point_t b, int *dist, mlx_image_t *fdf)
{
	float	f;
	int		i;
	float	rgba[4];

	i = 0;
	f = dist[1] / 2;
	calc_gradient_steps(dist[1], a.color, b.color, &*rgba);
	while (b.y < a.y)
	{
		mlx_put_pixel(fdf, a.x, a.y, calc_gradient_color(i, a.color, &*rgba));
		f = f - dist[0];
		if (f < 0)
		{
			a.x++;
			f = f + dist[1];
		}
		a.y--;
		i++;
	}
}

void	draw_line_up(point_t a, point_t b, mlx_image_t *fdf)
{
	int		dx;
	int		dy;
	int		dist[2];

	dx = b.x - a.x;
	dy = a.y - b.y;
	dist[0] = dx;
	dist[1] = dy;
	if (dx > dy)
		draw_line_up_x_long(a, b, dist, fdf);
	else
		draw_line_up_y_long(a, b, dist, fdf);
}

void	draw_line(point_t point_a, point_t point_b, mlx_image_t *fdf)
{
	if (point_a.x <= point_b.x)
	{
		if (point_a.y < point_b.y)
			draw_line_down(point_a, point_b, fdf);
		else
			draw_line_up(point_a, point_b, fdf);
	}
	else
	{
		if (point_a.y < point_b.y)
			draw_line_down(point_b, point_a, fdf);
		else
			draw_line_up(point_b, point_a, fdf);
	}
}

point_t	point_project(int x, int y, int z, fdf_t *fdf)
{
	point_t rtn;

	if (fdf->top == 1)
	{
	rtn.x = 10 + x * fdf->zoom;
	rtn.y = 10 + y * fdf->zoom;
	rtn.z = z;
	//ft_printf("%i %i %i\n", rtn.x, rtn.y, rtn.z);
	fdf->iso = 0;
	}

	// ISO top view
	if (fdf->iso == 1)
	{
	rtn.x = 100 + x * fdf->zoom + y * fdf->zoom;
	rtn.y = 400 + y * fdf->zoom/2 - x  * fdf->zoom/2 - z * fdf->zoom/2;
	//ft_printf("ISO ON%i\n", rtn.y);
	rtn.z = z;
		//ft_printf("%i %i %i\n", rtn.x, rtn.y, rtn.z);
	fdf->top = 0;
	}
	return (rtn);
}

void	draw_map(fdf_t* fdf)
{
	size_t	x;
	size_t	y;
	point_t	point_a;
	point_t	point_b;

	ft_memset(fdf->img_fdf->pixels, 35, fdf->img_fdf->width * fdf->img_fdf->height * sizeof(int32_t));
	y = 0;
	while (y < fdf->map->row)
	{
		x = 0;
		while (x < fdf->map->col)
		{
			point_a = point_project(x, y, fdf->map->coordinate[y][x].height, fdf);
			point_a.color = fdf->map->coordinate[y][x].color;
			if (x < fdf->map->col - 1)
			{
				point_b = point_project(x + 1, y, fdf->map->coordinate[y][x + 1].height, fdf);
				point_b.color = fdf->map->coordinate[y][x + 1].color;
				draw_line(point_a, point_b, fdf->img_fdf);
			}
			if (y < fdf->map->row - 1)
			{
				point_b = point_project(x, y + 1, fdf->map->coordinate[y + 1][x].height, fdf);
				point_b.color = fdf->map->coordinate[y + 1][x].color;
				draw_line(point_a, point_b, fdf->img_fdf);
			}
			x++;
		}
		y++;
	}
	mlx_image_to_window(fdf->mlx, fdf->img_fdf, 0, 0);
	text_info(fdf->mlx, fdf->name, fdf->map);
}

/* void	draw_map(map_t map, mlx_image_t* fdf)
{
	size_t	c;
	size_t	r;
	point_t	point_a;
	point_t	point_b;
	int	space = 30;

	c = 0;
	r = 0;
	point_b.x = 100;
	point_b.y = 100;
	point_b.color = map.coordinate[r][c].color;
	while (map.row > r)
	{
		while (map.col > c + 1)
		{
			point_a = point_b;
			point_b.x = point_a.x + space*1;
			point_b.y = point_a.y;
			point_b.color = map.coordinate[r][c + 1].color;
			draw_line(point_a, point_b, fdf);
			c++;
		}
		point_b.x = 100;
		point_b.y = point_a.y + space*1;
		c = 0;
		r++;
	}
	c = 0;
	r = 0;
	point_b.x = 100;
	point_b.y = 100;
	point_b.color = map.coordinate[r][c].color;

	while (map.col > c + 0)
	{
		while (map.row > r + 1)
			{
				point_a = point_b;
				point_b.x = point_a.x;
				point_b.y = point_a.y + space*1;
				point_b.color = map.coordinate[r + 1][c].color;
				draw_line(point_a, point_b, fdf);
				r++;
			}
		point_b.x = point_a.x + space*1;
		point_b.y = 100;
		r = 0;
		c++;
	} */
