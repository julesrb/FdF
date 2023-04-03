/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:17:14 by jubernar          #+#    #+#             */
/*   Updated: 2022/12/02 12:17:19 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>


typedef struct intersection
{
	int	height;
	int	color;
}	intersection_t;

typedef struct map
{
	size_t		row;
	size_t		col;
	intersection_t **coordinate;
}	map_t;

typedef struct point
{
	int		x;
	int		y;
	int	color;
}	point_t;

void	draw_map(map_t map, mlx_image_t* fdf);
void draw_line(point_t point_a, point_t point_b, mlx_image_t *fdf);

#endif