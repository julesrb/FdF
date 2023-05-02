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

/* typedef struct env
{
	int 	offset;
	float	zoom;
	int		iso;
	int		top;
}	env_t; */

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
	int		z;
	int		color;
}	point_t;

typedef struct fdf
{
	char*			name;
	int				offset;
	float			zoom;
	int				iso;
	int				top;
	map_t*			map;
	mlx_image_t*	img_bck;
	mlx_image_t*	img_fdf;
	mlx_t*			mlx;
}	fdf_t;


void	draw_map(fdf_t *fdf);
int		parse_map(char *file_name, map_t* map);
void	draw_line(point_t point_a, point_t point_b, mlx_image_t *fdf);
void	text_info(mlx_t *mlx, char *argv, map_t *map);

#endif