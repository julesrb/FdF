/* need to inc for open  */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fdf.h"
#define WIDTH 1080
#define HEIGHT 720


void	text_info(mlx_t *mlx, char *name, map_t *map)
{

	mlx_put_string(mlx, "NAME", 20, 25);
	mlx_put_string(mlx, ft_strchr(name, '/'), 100, 25);
	mlx_put_string(mlx, "WIDTH", 20, 50);
	mlx_put_string(mlx, ft_itoa(map->col), 100, 50);
	mlx_put_string(mlx, "LENGHT", 20, 75);
	mlx_put_string(mlx, ft_itoa(map->row), 100, 75);

	mlx_put_string(mlx, "CONTROL", 20, 600);
	mlx_put_string(mlx, "Zoom in:  I", 20, 625);
	mlx_put_string(mlx, "Zoom out: O", 20, 650);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	fdf_t	*fdf;
	fdf = (fdf_t*)param;

	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
	{
		fdf->zoom = fdf->zoom * 1.1;
	}
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		fdf->zoom = fdf->zoom * 0.90;
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		fdf->top = 1;
		fdf->iso = 0;
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		fdf->iso = 1;
		fdf->top = 0;
	}
	draw_map(fdf);
	(void)param;
}

fdf_t	*fdf_init(char* name)
{
	fdf_t			*fdf;
	fdf = ft_calloc(1, sizeof(fdf_t));
	fdf->name = ft_strdup(name);
	fdf->map = ft_calloc(1, sizeof(map_t));

	fdf->iso = 1;
	fdf->zoom = 3;

	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	// include mlx errno and exit and resizing.

	fdf->img_bck = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img_fdf = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	// include mlx errno and exit 

	return (fdf);
}

int32_t	main (int argc, char *argv[])
{
	fdf_t			*fdf;

	if (argc != 2)
		return (ft_printf("!! Incorrect number of arguments !!"));
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == 0)
		return (ft_printf("!! Wrong extension !!"));

	fdf = fdf_init(argv[1]);
	if (parse_map(argv[1], fdf->map) == -1)
		return (0);

	//setting the background color
	ft_memset(fdf->img_bck->pixels, 35, fdf->img_bck->width * fdf->img_bck->height * sizeof(int32_t));
	mlx_image_to_window(fdf->mlx, fdf->img_bck, 0, 0);

	draw_map(fdf);

	//text_info(fdf.mlx, argv[1], &fdf.map);
	mlx_key_hook(fdf->mlx, &my_keyhook, fdf);
	mlx_loop(fdf->mlx);
	// do i need mlx_delete_image ?
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}