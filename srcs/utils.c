/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 17:09:38 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/04 17:09:38 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			ft_distancec(t_camera c, t_pos p2)
{
	p2.x = c.x - p2.x;
	p2.y = c.y - p2.y;
	p2.z = c.z - p2.z;
	return (sqrt((p2.x * p2.x) + (p2.y * p2.y) + (p2.z * p2.z)));
}

double			ft_abs(double n)
{
	return ((n < 0) ? -n : n);
}

double			ft_max(double a, double b)
{
	return ((a > b) ? a : b);
}
