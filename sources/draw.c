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

void	draw_line(t_point point_a, t_point point_b, mlx_image_t *fdf)
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

t_point	point_project(int x, int y, int z, t_fdf *fdf)
{
	t_point	rtn;

	if (fdf->top == 1)
	{
		rtn.x = x * fdf->zoom + fdf->offset_x;
		rtn.y = y * fdf->zoom + fdf->offset_y;
		rtn.z = z;
		fdf->iso = 0;
		rtn.x = rtn.x + WIDTH / 2 - fdf->map->col / 2 * fdf->zoom;
		rtn.y = rtn.y + HEIGHT / 2 - fdf->map->row / 2 * fdf->zoom;
	}
	if (fdf->iso == 1)
	{
		rtn.x = x * fdf->zoom + y * fdf->zoom + fdf->offset_x;
		rtn.y = y * fdf->zoom / 2 - x * fdf->zoom / 2 - z * fdf->zoom / 2
			+ fdf->offset_y;
		rtn.z = z;
		fdf->top = 0;
		rtn.x = rtn.x + WIDTH / 2 - ((fdf->map->col - 1) * fdf->zoom
				+ (fdf->map->row - 1) * fdf->zoom) / 2;
		rtn.y = rtn.y + HEIGHT / 2 - (fdf->map->row * fdf->zoom / 2
				- fdf->map->col * fdf->zoom / 2) / 2;
	}
	return (rtn);
}

void	draw_grey_background(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
		ptr[i] = (unsigned char)c;
		i++;
		ptr[i] = (unsigned char)c;
		i++;
		ptr[i] = 255;
		i++;
	}
}

void	draw_from_point(t_fdf *fdf, size_t y, size_t x)
{
	t_point	point_a;
	t_point	point_b;

	point_a = point_project(x, y, fdf->map->grid[y][x].height, fdf);
	point_a.color = fdf->map->grid[y][x].color;
	if (x < fdf->map->col - 1)
	{
		point_b = point_project(x + 1, y, fdf->map->grid[y][x + 1].height, fdf);
		point_b.color = fdf->map->grid[y][x + 1].color;
		draw_line(point_a, point_b, fdf->img);
	}
	if (y < fdf->map->row - 1)
	{
		point_b = point_project(x, y + 1, fdf->map->grid[y + 1][x].height, fdf);
		point_b.color = fdf->map->grid[y + 1][x].color;
		draw_line(point_a, point_b, fdf->img);
	}
}

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	draw_grey_background(fdf->img->pixels, 35,
		fdf->img->width * fdf->img->height * sizeof(int32_t));
	y = 0;
	while (y < fdf->map->row)
	{
		x = 0;
		while (x < fdf->map->col)
		{
			draw_from_point(fdf, y, x);
			x++;
		}
		y++;
	}
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	text_info(fdf->mlx, fdf->name, fdf->map);
}
