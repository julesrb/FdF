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

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <errno.h>

# define WIDTH 1080
# define HEIGHT 720

typedef struct grid
{
	int	height;
	int	color;
}	t_grid;

typedef struct map
{
	size_t		row;
	char		*row_c;
	size_t		col;
	char		*col_c;
	t_grid		**grid;
}	t_map;

typedef struct point
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

typedef struct fdf
{
	char			*name;
	float			zoom;
	int				iso;
	int				top;
	int				offset_x;
	int				offset_y;
	t_map			*map;
	mlx_image_t		*img;
	mlx_t			*mlx;
}	t_fdf;

void	draw_map(t_fdf *fdf);
int		parse_map(char *file_name, t_map *map);
void	text_info(mlx_t *mlx, char *argv, t_map *map);

uint8_t	ft_atohex(char *str);
int		ft_ahextorgba(char *str);
void	calc_grad_steps(int i, int cl_a, int cl_b, float rgba[4]);
int		calc_grad_color(int steps, int cl_a, float rgba[4]);

void	draw_line(t_point point_a, t_point point_b, mlx_image_t *fdf);
void	draw_line_down(t_point a, t_point b, mlx_image_t *fdf);
void	draw_line_up(t_point a, t_point b, mlx_image_t *fdf);

int		count_split(char **split);
int		count_map_colums(char *file_name, t_map *map);
int		count_map_row(char *file_name, t_map *map);

int		free_split(char **split);

void	my_keyhook(mlx_key_data_t keydata, void *param);

void	terminate(char *str);
void	win_close(void *param);
int		free_grid(t_grid **grid, t_fdf *fdf);
#endif