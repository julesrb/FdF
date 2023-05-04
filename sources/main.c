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

void	text_info(mlx_t *mlx, char *name, map_t *map)
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

int	free_grid(grid_t **grid, fdf_t *fdf)
{
	size_t	i;

	i = 0;
	while (fdf->map->row > i)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (0);
}

void	win_close(void *param)
{
	fdf_t	*fdf;

	fdf = (fdf_t *)param;
	free(fdf->map->row_c);
	free(fdf->map->col_c);
	free_grid(fdf->map->grid, fdf);
	free(fdf->map);
	free(fdf->name);
	free(fdf);
}

fdf_t	*fdf_init(char *name)
{
	fdf_t	*fdf;

	fdf = ft_calloc(1, sizeof(fdf_t));
	fdf->name = ft_strdup(name);
	fdf->map = ft_calloc(1, sizeof(map_t));
	fdf->iso = 1;
	fdf->zoom = 3;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	return (fdf);
}

int32_t	main(int argc, char *argv[])
{
	fdf_t	*fdf;

	if (argc != 2)
		return (ft_printf("!! Incorrect number of arguments !!"));
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
		return (ft_printf("!! Wrong extension !!"));
	fdf = fdf_init(argv[1]);
	if (parse_map(argv[1], fdf->map) == -1)
		return (0);
	draw_map(fdf);
	mlx_key_hook(fdf->mlx, &my_keyhook, fdf);
	mlx_close_hook(fdf->mlx, &win_close, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
