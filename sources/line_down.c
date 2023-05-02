/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
