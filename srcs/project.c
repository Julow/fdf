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

	r = ft_distancec(env->camera, pos);
	pos.x += r * cos(env->camera.p) * sin(env->camera.t);
	pos.y += r * sin(env->camera.p) * sin(env->camera.t);
	pos.z += r * cos(env->camera.t);
	pt.x = ((pos.x - env->camera.x) * (r / pos.z));
	pt.y = ((pos.y - env->camera.y) * (r / pos.z));
	return (pt);
}
