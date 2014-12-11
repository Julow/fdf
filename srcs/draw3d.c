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

void			ft_3dput(t_env *env, t_pos pos, int color)
{
	t_pt			pt;

	pt = env->project(env, pos);
	pt.x += env->offset.x;
	pt.y += env->offset.y;
	color += (int)(pos.z * 20) << 16;
	color -= (int)(pos.z * 20) << 8;
	color -= (int)(pos.z * 20);
	ft_drawpt(env->img, pt, color);
}

void			draw3d_line(t_env *env, t_pos p1, t_pos p2, int color)
{
	t_pos			delta;
	double			pts;

	delta = POS(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	pts = MAX(MAX(ABS(delta.x), ABS(delta.y)), ABS(delta.z)) * 80;
	delta.x /= pts;
	delta.y /= pts;
	delta.z /= pts;
	while (--pts >= -1)
	{
		ft_3dput(env, p1, color);
		p1.x += delta.x;
		p1.y += delta.y;
		p1.z += delta.z;
	}
}
