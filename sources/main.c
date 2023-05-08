/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	text_info(mlx_t *mlx, char *name, t_map *map)
{
	mlx_put_string(mlx, "NAME", 20, 25);
	mlx_put_string(mlx, ft_strchr(name, '/'), 100, 25);
	mlx_put_string(mlx, "WIDTH", 20, 50);
	mlx_put_string(mlx, map->col_c, 100, 50);
	mlx_put_string(mlx, "LENGHT", 20, 75);
	mlx_put_string(mlx, map->row_c, 100, 75);
	mlx_put_string(mlx, "CONTROL", 20, 600);
	mlx_put_string(mlx, "Zoom in:  I", 20, 625);
	mlx_put_string(mlx, "Zoom out: O", 20, 650);
}

t_fdf	*fdf_init(char *name)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		terminate("fdf init error");
	fdf->name = ft_strdup(name);
	if (!fdf->name)
		terminate("fdf init error");
	fdf->map = ft_calloc(1, sizeof(t_map));
	if (!fdf->map)
		terminate("fdf init error");
	fdf->iso = 1;
	fdf->zoom = 3;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	if (!fdf->mlx)
		terminate("fdf init error");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		terminate("fdf init error");
	return (fdf);
}

int32_t	main(int argc, char *argv[])
{
	t_fdf	*fdf;

	if (argc != 2)
		terminate("Incorrect number of arguments !");
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
		terminate("Wrong extension !");
	fdf = fdf_init(argv[1]);
	parse_map(argv[1], fdf->map);
	draw_map(fdf);
	mlx_key_hook(fdf->mlx, &my_keyhook, fdf);
	mlx_close_hook(fdf->mlx, &win_close, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
