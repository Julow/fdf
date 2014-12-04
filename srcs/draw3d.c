/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 15:59:43 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/04 15:59:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	ft_abs(double n)
{
	return ((n < 0) ? -n : n);
}

static double	ft_max(double a, double b)
{
	return ((a > b) ? a : b);
}

void			draw3d_line(t_env *env, t_pos p1, t_pos p2, int color)
{
	t_pos			delta;
	double			pts;

	delta = POS(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	pts = ft_max(ft_max(ft_abs(delta.x), ft_abs(delta.y)), ft_abs(delta.z));
	delta.x /= pts;
	delta.y /= pts;
	delta.z /= pts;
	while (--pts >= -1)
	{
		mlx_pixel_put(env->mlx, env->win, p1.x, p1.y, color);
		p1.x += delta.x;
		p1.y += delta.y;
		p1.z += delta.z;
	}
}
