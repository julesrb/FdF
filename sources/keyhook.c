/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_keyhook_1(mlx_key_data_t keydata, void *param)
{
	fdf_t	*fdf;

	fdf = (fdf_t *)param;
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


void	my_keyhook_2(mlx_key_data_t keydata, void *param)
{
	fdf_t	*fdf;

	fdf = (fdf_t *)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		fdf->offset_y = fdf->offset_y + 30;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		fdf->offset_y = fdf->offset_y - 30;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		fdf->offset_x = fdf->offset_x - 30;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		fdf->offset_x = fdf->offset_x + 30;
	}
	draw_map(fdf);
	(void)param;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	my_keyhook_1(keydata, param);
	my_keyhook_2(keydata, param);
}
