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
	double const	c1 = 0.5;
	double const	c2 = 0.75;

	pt.x = ROUND(c1 * pos.x - c2);
	pt.y = ROUND(-pos.z + (c1 / 2 * pos.x) + (c2 / 2 * pos.y));
	(void)env;
	return (pt);
}
