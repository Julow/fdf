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

t_pt			project_para(t_pos pos)
{
	t_pt			pt;

	pt.x = ROUND(pos.x + -3 * pos.z);
	pt.y = ROUND(pos.y + -1.5 * pos.z);
	return (pt);
}

t_pt			project_iso(t_pos pos)
{
	t_pt			pt;

	pt.x = ROUND(0.6 * pos.x - 0.6 * pos.y);
	pt.y = ROUND(-pos.z + 0.3 * pos.x + 0.3 * pos.y);
	return (pt);
}
