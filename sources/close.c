#include "fdf.h"

int	free_grid(t_grid **grid, t_fdf *fdf)
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
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	free(fdf->map->row_c);
	free(fdf->map->col_c);
	free_grid(fdf->map->grid, fdf);
	free(fdf->map);
	free(fdf->name);
	free(fdf);
}

void	terminate(char *str)
{
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(EXIT_FAILURE);
}
