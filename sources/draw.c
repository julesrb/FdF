/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	point_t	rtn;

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
		rtn.y = 400 + y * fdf->zoom / 2 - x * fdf->zoom / 2 - z * fdf->zoom / 2;
		//ft_printf("ISO ON%i\n", rtn.y);
		rtn.z = z;
			//ft_printf("%i %i %i\n", rtn.x, rtn.y, rtn.z);
		fdf->top = 0;
	}
	return (rtn);
}

void	draw_map(fdf_t *fdf)
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
			point_a = point_project(x, y, fdf->map->grid[y][x].height, fdf);
			point_a.color = fdf->map->grid[y][x].color;
			if (x < fdf->map->col - 1)
			{
				point_b = point_project(x + 1, y, fdf->map->grid[y][x + 1].height, fdf);
				point_b.color = fdf->map->grid[y][x + 1].color;
				draw_line(point_a, point_b, fdf->img_fdf);
			}
			if (y < fdf->map->row - 1)
			{
				point_b = point_project(x, y + 1, fdf->map->grid[y + 1][x].height, fdf);
				point_b.color = fdf->map->grid[y + 1][x].color;
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
	point_b.color = map.grid[r][c].color;
	while (map.row > r)
	{
		while (map.col > c + 1)
		{
			point_a = point_b;
			point_b.x = point_a.x + space*1;
			point_b.y = point_a.y;
			point_b.color = map.grid[r][c + 1].color;
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
	point_b.color = map.grid[r][c].color;

	while (map.col > c + 0)
	{
		while (map.row > r + 1)
			{
				point_a = point_b;
				point_b.x = point_a.x;
				point_b.y = point_a.y + space*1;
				point_b.color = map.grid[r + 1][c].color;
				draw_line(point_a, point_b, fdf);
				r++;
			}
		point_b.x = point_a.x + space*1;
		point_b.y = 100;
		r = 0;
		c++;
	} */
