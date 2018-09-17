/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmulamba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:22:59 by bmulamba          #+#    #+#             */
/*   Updated: 2018/09/15 08:48:57 by bmulamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "minilibx_macos/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WIN_H		1400
# define WIN_W		1000
# define R			50

typedef unsigned int	t_int;
typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef enum		e_type
{
	SPHERE,
	CYLINDER,
	CONE,
	PLAN
}					t_type;

typedef struct		s_obj
{
	t_type			type;
	t_vect			pos;
	t_vect			rot;
	t_int			color;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_img
{
	void			*ptr;
	char			*data;
	int				x;
	int				y;
	int				bpp;
	int				sline;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	t_img			image;
	t_obj			*objs;
	t_vect			eye;
	t_vect			eyerot;
	t_vect			plan;
	t_vect			vector;
	t_vect			spot;
	t_vect			spot1;
	double			focale;
	double			k;
	t_obj			*cur_obj;
}					t_mlx;

void				calc_rtv1(t_mlx *mlx);
void				all_rot(t_vect *xyz, t_vect *rot, int invert);
void				put_pixel(t_mlx *mlx, int x, int y, t_int color);
void				ft_putstr(const char *str);
int					puterror(char *str);
int					key_hook(int keycode, t_mlx *mlx);
int					key_release(void);
int					expose_hook(t_mlx *mlx);
t_obj				*obj_new(t_type type, t_vect pos,
							t_vect rot, t_int color);
void				stack_obj(t_obj **list, t_obj *new);
void				calc_sphere(t_vect *eye, t_vect *vector, double *k);
void				calc_cylinder(t_vect *eye, t_vect *vector, double *k);
void				calc_cone(t_vect *eye, t_vect *vector, double *k);
void				calc_plan(t_vect *eye, t_vect *vector, double *k);
void				calc_curobj(t_vect *eye, t_vect *vector,
								t_obj *obj, double *k);
t_int				calc_light(t_mlx *mlx, t_vect *spot);
t_int				shadow_cast(t_mlx *mlx, t_vect *spot, t_int cur_color);
t_int				mult_color(t_int color, double perc);
t_int				add_2color(t_int color1, t_int color2);
void				move_eye(t_vect *eye, t_vect *vector,
								t_obj *tmp, int invert);
#endif
