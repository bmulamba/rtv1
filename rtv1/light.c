/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmulamba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:18:01 by bmulamba          #+#    #+#             */
/*   Updated: 2018/09/13 10:58:51 by bmulamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		norme_vector(t_vect *xyz)
{
	double	res;

	res = sqrt(pow(xyz->x, 2) + pow(xyz->y, 2) + pow(xyz->z, 2));
	return (res);
}

void		get_normal(t_vect *normal, t_vect *p, t_obj *obj)
{
	if (obj->type == SPHERE)
		*normal = (t_vect){p->x, p->y, p->z};
	else if (obj->type == CYLINDER)
		*normal = (t_vect){p->x, p->y, 0};
	else if (obj->type == CONE)
		*normal = (t_vect){p->x, p->y, -0.7 * p->z};
	else if (obj->type == PLAN)
		*normal = (t_vect){0, 0, 100};
}

t_int		calc_light(t_mlx *mlx, t_vect *spot)
{
	t_vect	p;
	t_vect	light;
	t_vect	normal;
	double	cos_a;
	t_int	new_color;

	p = (t_vect){mlx->eye.x + mlx->k * mlx->vector.x,
				mlx->eye.y + mlx->k * mlx->vector.y,
				mlx->eye.z + mlx->k * mlx->vector.z};
	light = (t_vect){spot->x - p.x, spot->y - p.y, spot->z - p.z};
	new_color = mlx->cur_obj->color;
	get_normal(&normal, &p, mlx->cur_obj);
	cos_a = (normal.x * light.x + normal.y * light.y + normal.z * light.z)
		/ (norme_vector(&normal) * norme_vector(&light));
	new_color = (cos_a >= 0 && cos_a <= 1)
		? mult_color(mlx->cur_obj->color, cos_a) : 0;
	return (new_color);
}
