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

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>

# define WIDTH 1080
# define HEIGHT 720

/* typedef struct env
{
	int 	offset;
	float	zoom;
	int		iso;
	int		top;
}	env_t; */

typedef struct grid
{
	int	height;
	int	color;
}	grid_t;

typedef struct map
{
	size_t		row;
	char		*row_c;
	size_t		col;
	char		*col_c;
	grid_t **grid;
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

uint8_t	ft_atohex(char *str);
int		ft_ahextorgba(char *str);
void	calc_grad_steps(int i, int cl_a, int cl_b, float rgba[4]);
int		calc_grad_color(int steps, int cl_a, float rgba[4]);

void	draw_line_down(point_t a, point_t b, mlx_image_t *fdf);
void	draw_line_down_y_long(point_t a, point_t b, int *dist, mlx_image_t *fdf);
void	draw_line_down_x_long(point_t a, point_t b, int *dist, mlx_image_t *fdf);

void	draw_line_up_x_long(point_t a, point_t b, int *dist, mlx_image_t *fdf);
void	draw_line_up_y_long(point_t a, point_t b, int *dist, mlx_image_t *fdf);
void	draw_line_up(point_t a, point_t b, mlx_image_t *fdf);

int		count_split(char **split);
int		count_map_colums(char *file_name, map_t *map);
int		count_map_row(char *file_name, map_t *map);

int	free_split(char **split);
#endif