/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmulamba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:16:18 by bmulamba          #+#    #+#             */
/*   Updated: 2018/09/13 14:16:18 by bmulamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(t_mlx *mlx, int x, int y, t_int color)
{
	int		i;
	int		j;
	t_int	new_color;

	new_color = mlx_get_color_value(mlx->ptr, color);
	j = y * mlx->image.sline + x * mlx->image.bpp;
	i = -1;
	while (++i < mlx->image.bpp)
	{
		if (mlx->image.endian == 0)
			mlx->image.data[j + i] = new_color >> (i << 3) & 0xFF;
		else
			mlx->image.data[y + i] = new_color >>\
			(mlx->image.bpp - ((i + 1) << 3)) & 0xFF;
	}
}

t_int	mult_color(t_int color, double perc)
{
	int		i;
	int		n_color[3];

	i = -1;
	while (++i < 3)
	{
		n_color[i] = (color >> ((2 - i) << 3)) & 0xFF;
		n_color[i] = n_color[i] * perc;
		n_color[i] = (n_color[i] > 0xFF ? 0xFF : n_color[i]);
		n_color[i] = (n_color[i] < 0 ? 0 : n_color[i]);
	}
	return ((n_color[0] << 16) + (n_color[1] << 8) + n_color[2]);
}

t_int	add_2color(t_int color1, t_int color2)
{
	int		i;
	int		n_color1[3];
	int		n_color2[3];

	i = -1;
	while (++i < 3)
	{
		n_color1[i] = (color1 >> ((2 - i) << 3)) & 0xFF;
		n_color2[i] = (color2 >> ((2 - i) << 3)) & 0xFF;
		n_color1[i] = n_color1[i] + n_color2[i];
		n_color1[i] = (n_color1[i] > 0xFF ? 0xFF : n_color1[i]);
		n_color1[i] = (n_color1[i] < 0 ? 0 : n_color1[i]);
	}
	return ((n_color1[0] << 16) + (n_color1[1] << 8) + n_color1[2]);
}

int		expose_hook(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->image.ptr, 0, 0);
	return (0);
}
