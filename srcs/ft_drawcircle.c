/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawcircle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 14:48:13 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/11 14:48:14 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_draw.h"

void			ft_drawcircle(t_image *img, t_pt center, int radius, int color)
{
	t_pt			pt;
	int				err;

	pt = PT(-radius, 0);
	err = 2 - (2 * radius);
	while (pt.x <= 0)
	{
		ft_drawxy(img, center.x - pt.x, center.y + pt.y, color);
		ft_drawxy(img, center.x - pt.y, center.y - pt.x, color);
		ft_drawxy(img, center.x + pt.x, center.y - pt.y, color);
		ft_drawxy(img, center.x + pt.y, center.y + pt.x, color);
		radius = err;
		if (radius <= pt.y)
		{
			pt.y++;
			err += pt.y * 2 + 1;
		}
		if (radius > pt.x || err > pt.y)
		{
			pt.x++;
			err += pt.x * 2 + 1;
		}
	}
}
