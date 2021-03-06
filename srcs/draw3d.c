/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 15:59:43 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/03 12:51:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pt			project_iso(t_pos pos)
{
	t_pt			pt;

	pt.x = ROUND(0.6 * pos.x - 0.6 * pos.y);
	pt.y = ROUND(-pos.z + 0.3 * pos.x + 0.3 * pos.y);
	return (pt);
}

void			ft_3dput(t_env *env, t_pos pos)
{
	t_pt			pt;

	pos.x *= env->pt_dist;
	pos.y *= env->pt_dist;
	pt = project_iso(pos);
	pt.x += env->offset.x;
	pt.y += env->offset.y;
	ft_drawpt(env->img, pt, gradientget(env->gradient,
		ft_posd(env->min_z, env->max_z, pos.z)));
}

void			draw3d_line(t_env *env, t_pos p1, t_pos p2)
{
	t_pos			delta;
	double			pts;

	delta = POS(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	pts = MAX(MAX(ABS(delta.x), ABS(delta.y)) * env->pt_dist, ABS(delta.z));
	delta.x /= pts;
	delta.y /= pts;
	delta.z /= pts;
	while (--pts >= -1)
	{
		ft_3dput(env, p1);
		p1.x += delta.x;
		p1.y += delta.y;
		p1.z += delta.z;
	}
}
