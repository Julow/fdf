/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:38:08 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/04 16:38:10 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pt			project_test(t_env *env, t_pos pos)
{
	t_pt			pt;
	double			r;
	double			t;
	double			p;

	r = ft_distancec(env->camera, pos);
	t = acos((pos.z - env->camera.z) / r);
	p = atan((pos.y - env->camera.y) / (pos.x - env->camera.x));
	t += env->camera.t;
	p += env->camera.p;
	pos.x = r * sin(t) * cos(p);
	pos.y = r * sin(t) * sin(p);
	pos.z = r * cos(t);
	pt.x = pos.x;
	pt.y = pos.y;
	return (pt);
}
