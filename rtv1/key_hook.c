/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmulamba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:17:29 by bmulamba          #+#    #+#             */
/*   Updated: 2018/09/14 11:27:35 by bmulamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;
	if (keycode == 53 && write(1, "End of Program!\n", 16))
		exit(EXIT_FAILURE);
	return (0);
}

int		key_release(void)
{
	write(1, "End of Program!\n", 16);
	exit(EXIT_FAILURE);
	return (0);
}
