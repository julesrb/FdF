/* need to inc for open  */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fdf.h"
#define WIDTH 1080
#define HEIGHT 720

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


// Reduce code with math absolute values 

// do the switch before sending to functions

// fix the color pick on the grid 

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

	if (dy < dx)
	{
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
	else
	{
		ft_printf("*");
		calculate_gradient_steps(dy, a.color, b.color, &*RGBA_steps);
		while(a.y < b.y)
		{
			mlx_put_pixel(fdf, a.x, a.y, calculate_gradient_color(i, a.color, &*RGBA_steps));
			if(p >= 0)
			{
				a.x++;
				p = p + 2 * dx - 2 * dy;
			}
			else
				p = p + 2 * dx;
		a.y++;
		i++;
		}
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

void	draw_map(map_t map, mlx_image_t* fdf)
{
	size_t	c;
	size_t	r;
	point_t point_a;
	point_t point_b;
	int space = 30;

	c = 0;
	r = 0;
	point_b.x = 100;
	point_b.y = 100;
	point_b.color = map.coordinate[r][c].color;
	while (map.row > r + 0)
	{
		while (map.col > c + 1)
		{
			point_a.x = point_b.x;
			point_a.y = point_b.y;
			point_a.color = point_b.color;
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
				point_a.x = point_b.x;
				point_a.y = point_b.y;
				point_a.color = point_b.color;
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
	}
}
