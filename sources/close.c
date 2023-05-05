/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	mlx_terminate(fdf->mlx);
}

void	terminate(char *str)
{
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(EXIT_FAILURE);
}
