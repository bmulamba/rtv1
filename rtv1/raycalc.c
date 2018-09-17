/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycalc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmulamba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 06:25:07 by bmulamba          #+#    #+#             */
/*   Updated: 2018/09/13 10:58:24 by bmulamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		move_eye(t_vect *eye, t_vect *vector, t_obj *tmp, int invert)
{
	if (invert == 1)
	{
		all_rot(eye, &tmp->rot, invert);
		all_rot(vector, &tmp->rot, invert);
	}
	eye->x += invert * tmp->pos.x;
	eye->y += invert * tmp->pos.y;
	eye->z += invert * tmp->pos.z;
	vector->x += invert * tmp->pos.x;
	vector->y += invert * tmp->pos.y;
	vector->z += invert * tmp->pos.z;
	if (invert == -1)
	{
		all_rot(eye, &tmp->rot, invert);
		all_rot(vector, &tmp->rot, invert);
	}
}

void		calc_curobj(t_vect *eye, t_vect *vector, t_obj *obj, double *k)
{
	move_eye(eye, vector, obj, -1);
	if (obj->type == SPHERE)
		calc_sphere(eye, vector, k);
	else if (obj->type == CYLINDER)
		calc_cylinder(eye, vector, k);
	else if (obj->type == CONE)
		calc_cone(eye, vector, k);
	else if (obj->type == PLAN)
		calc_plan(eye, vector, k);
	move_eye(eye, vector, obj, 1);
}

static void	calc_inter(int x, int y, t_mlx *mlx)
{
	double	k[2];
	t_obj	*tmp;
	t_int	color;

	mlx->k = 0xFFFFFFFF;
	mlx->cur_obj = NULL;
	tmp = mlx->objs;
	while (tmp)
	{
		calc_curobj(&mlx->eye, &mlx->vector, tmp, k);
		if (k[0] >= 0 && mlx->k > k[0] && (mlx->cur_obj = tmp))
			mlx->k = k[0];
		if (k[1] >= 0 && mlx->k > k[1] && (mlx->cur_obj = tmp))
			mlx->k = k[1];
		tmp = tmp->next;
	}
	if (mlx->cur_obj != NULL)
	{
		color = calc_light(mlx, &mlx->spot);
		color = add_2color(color, calc_light(mlx, &mlx->spot1));
		color = mult_color(color, 0.7);
		color = shadow_cast(mlx, &mlx->spot, color);
		color = shadow_cast(mlx, &mlx->spot1, color);
		put_pixel(mlx, x, y, color);
	}
}

static void	calc_ray_xy(int x, int y, t_mlx *mlx)
{
	mlx->plan.x = mlx->focale;
	mlx->plan.y = (WIN_H / 2.0) - x;
	mlx->plan.z = (WIN_W / 2.0) - y;
	mlx->vector.x = mlx->plan.x - mlx->eye.x;
	mlx->vector.y = mlx->plan.y - mlx->eye.z;
	mlx->vector.z = mlx->plan.z - mlx->eye.z;
	all_rot(&mlx->vector, &mlx->eyerot, 1);
	calc_inter(x, y, mlx);
}

void		calc_rtv1(t_mlx *mlx)
{
	int		x;
	int		y;
	int		prev_perc;

	all_rot(&mlx->eye, &mlx->eyerot, 1);
	x = -1;
	while (++x < WIN_H)
	{
		y = -1;
		while (++y < WIN_W)
		{
			calc_ray_xy(x, y, mlx);
			if (100 * (y + x * WIN_W) / (WIN_H * WIN_W) > prev_perc + 1)
			{
				prev_perc = 100 * (y + x * WIN_W) / (WIN_H * WIN_W);
			}
		}
	}
}
