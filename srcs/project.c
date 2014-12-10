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

	pt.x = ROUND(0.5 * pos.x - 0.75);
	pt.y = ROUND(-pos.z + (0.5 / 2 * pos.x) + (0.75 / 2 * pos.y));
/*
	pt.x = ROUND(pos.x + 0.5);
	pt.y = ROUND(pos.y + (0.75 / 2 * -pos.z));
*/
	(void)env;
	return (pt);
}
