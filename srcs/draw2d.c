/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 16:42:53 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/09 16:42:54 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void			ft_drawrect(t_env *env, t_rect rect, int color)
{
	t_rect			i;

	if (rect.width <= 0 || rect.height <= 0)
		return;
	rect.width += rect.x;
	rect.height += rect.y;
	i = rect;
	while (i.x < rect.width)
	{
		mlx_pixel_put(env->mlx, env->win, i.x, i.y, color);
		mlx_pixel_put(env->mlx, env->win, i.x, rect.height, color);
		i.x++;
	}
	i = rect;
	while (i.y < rect.height)
	{
		mlx_pixel_put(env->mlx, env->win, i.x, i.y, color);
		mlx_pixel_put(env->mlx, env->win, rect.width, i.y, color);
		i.y++;
	}
}

void			ft_drawrectf(t_env *env, t_rect rect, int color)
{
	t_pt			i;

	if (rect.width <= 0 || rect.height <= 0)
		return;
	rect.width += rect.x;
	rect.height += rect.y;
	i.y = rect.y - 1;
	while (++i.y < rect.height)
	{
		i.x = rect.x - 1;
		while (++i.x < rect.width)
			mlx_pixel_put(env->mlx, env->win, i.x, i.y, color);
	}
}

void			ft_drawcircle(t_env *env, t_pt cent, int radius, int color)
{
	t_pt			pt;
	int				err;

	pt = PT(-radius, 0);
	err = 2 - (2 * radius);
	while (pt.x <= 0)
	{
		mlx_pixel_put(env->mlx, env->win, cent.x - pt.x, cent.y + pt.y, color);
		mlx_pixel_put(env->mlx, env->win, cent.x - pt.y, cent.y - pt.x, color);
		mlx_pixel_put(env->mlx, env->win, cent.x + pt.x, cent.y - pt.y, color);
		mlx_pixel_put(env->mlx, env->win, cent.x + pt.y, cent.y + pt.x, color);
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

void			ft_drawline(t_env *env, t_pt p1, t_pt p2, int color)
{
	t_pt			delta;
	t_pt			dirr;
	int				err;

	delta = PT(ft_abs(p2.x - p1.x), -ft_abs(p2.y - p1.y));
	dirr = PT((p1.x < p2.x) ? 1 : -1, (p1.y < p2.y) ? 1 : -1);
	err = (delta.x + delta.y) * 2;
	while (TRUE)
	{
		mlx_pixel_put(env->mlx, env->win, p1.x, p1.y, color);
		if (err >= delta.y)
		{
			if (p1.x == p2.x)
				break ;
			err += delta.y * 2;
			p1.x += dirr.x;
		}
		if (err <= delta.x)
		{
			if (p1.y == p2.y)
				break ;
			err += delta.x * 2;
			p1.y += dirr.y;
		}
	}
}
