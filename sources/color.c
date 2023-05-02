/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:32 by jubernar          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:35 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* need to inc for open  */
#include "fdf.h"

void	calc_grad_steps(int i, int cl_a, int cl_b, float rgba[4])
{
	rgba[0] = (float)((uint8_t)(cl_b >> 24) - (uint8_t)(cl_a >> 24)) / (float)i;
	rgba[1] = (float)((uint8_t)(cl_b >> 16) - (uint8_t)(cl_a >> 16)) / (float)i;
	rgba[2] = (float)((uint8_t)(cl_b >> 8) - (uint8_t)(cl_a >> 8)) / (float)i;
	rgba[3] = (float)((uint8_t)(cl_b) - (uint8_t)(cl_a)) / (float)i;
}

int	calc_grad_color(int steps, int cl_a, float rgba[4])
{
	return (((int)((uint8_t)(cl_a >> 24) + steps * rgba[0]) & 0xFF) << 24 |
			((int)((uint8_t)(cl_a >> 16) + steps * rgba[1]) & 0xFF) << 16 |
			((int)((uint8_t)(cl_a >> 8) + steps * rgba[2]) & 0xFF) << 8 |
			((int)((uint8_t)(cl_a >> 0) + steps * rgba[3]) & 0xFF) << 0);
}

uint8_t	ft_atohex(char *str)
{
	uint8_t	a;
	uint8_t	b;

	if (str[0] >= '0' && str[0] <= '9')
		a = str[0] - 48;
	if (str[0] >= 'a' && str[0] <= 'f')
		a = str[0] - 87;
	if (str[0] >= 'A' && str[0] <= 'F')
		a = str[0] - 55;
	if (str[1] >= '0' && str[1] <= '9')
		b = str[1] - 48;
	if (str[1] >= 'a' && str[1] <= 'f')
		b = str[1] - 87;
	if (str[1] >= 'A' && str[1] <= 'F')
		b = str[1] - 55;
	return ((a * 16) + b);
}

int	ft_ahextorgba(char *str)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	int		i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (str[i] != 'x')
		i++;
	i++;
	r = ft_atohex(&str[i]);
	if (str[i + 2] != '\0')
	{
		g = ft_atohex(&str[i + 2]);
		if (str[i + 4] != '\0')
			b = ft_atohex(&str[i + 4]);
	}
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}
