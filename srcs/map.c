/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:00:48 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/07 16:20:23 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static t_bool	load_pts(t_env *env, t_tab *pts, char *line)
{
	int				i;
	double			tmp;
	t_bool			valid;

	valid = TRUE;
	i = 0;
	while (ft_iswhite(line[i]))
		i++;
	while (line[i] != '\0')
	{
		tmp = ft_atod(line + i);
		env->max_z = MAX(env->max_z, tmp);
		env->min_z = MIN(env->min_z, tmp);
		ft_tabadd(pts, &tmp);
		while (!ft_iswhite(line[i]) && line[i] != '\0')
		{
			if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
				valid = FALSE;
			i++;
		}
		while (ft_iswhite(line[i]))
			i++;
	}
	return (valid);
}

static void		get_maxmin(t_env *env, t_pt *max, t_pt *min)
{
	t_pt			i;
	t_tab			*line;
	t_pt			tmp;

	*max = PT(0, 0);
	*min = PT(WIDTH, HEIGHT);
	i = PT(-1, -1);
	while (++i.y < env->map->length)
	{
		line = AG(t_tab*, env->map, i.y);
		i.x = line->length;
		while (i.x-- > 0)
		{
			tmp = project_iso(POS(i.x * env->pt_dist, i.y * env->pt_dist,
				TG(double, line, i.x) * env->pt_dist / 10));
			max->x = MAX(max->x, tmp.x);
			max->y = MAX(max->y, tmp.y);
			min->x = MIN(min->x, tmp.x);
			min->y = MIN(min->y, tmp.y);
		}
	}
}

void			mapoffset(t_env *env)
{
	t_pt			max;
	t_pt			min;
	const t_pt		first = project_iso(POS(0, 0, 0));

	mlx_string_put(env->mlx, env->win, 50, 50, 0xFFFFFF, "Measuring map...");
	env->pt_dist = 1;
	get_maxmin(env, &max, &min);
	env->pt_dist = DEF_PTDIST;
	if (((max.x - min.x) * env->pt_dist) > WIDTH)
		env->pt_dist *= WIDTH / (env->pt_dist * (max.x - min.x));
	if (((max.y - min.y) * env->pt_dist) > HEIGHT)
		env->pt_dist *= HEIGHT / (env->pt_dist * (max.y - min.y));
	get_maxmin(env, &max, &min);
	env->offset.x = (WIDTH - ((max.x - min.x + first.x))) / 2;
	env->offset.y = (HEIGHT - ((max.y - min.y + first.y))) / 2;
	env->offset.x += (first.x - min.x);
	env->offset.y += (first.y - min.y);
	mlx_string_put(env->mlx, env->win, 200, 50, 0xFFFFFF, "done.");
}

t_bool			load_map(int fd, t_env *env)
{
	char			*line;
	t_tab			*tmp;
	t_bool			valid;

	mlx_string_put(env->mlx, env->win, 50, 35, 0xFFFFFF, "Loading map...");
	valid = TRUE;
	while (get_next_line(fd, &line) > 0 && line != NULL)
	{
		tmp = ft_tabnew(sizeof(double));
		if (!load_pts(env, tmp, line))
			valid = FALSE;
		ft_arrayadd(env->map, tmp);
	}
	mlx_string_put(env->mlx, env->win, 200, 35, 0xFFFFFF, "done.");
	return (valid);
}

void			draw_map(t_env *env)
{
	t_pt			pt;
	t_pos			pos;
	t_tab			*tmp;
	const double	pt_h = env->pt_dist / 10;

	mlx_string_put(env->mlx, env->win, 50, 65, 0xFFFFFF, "Rendering map...");
	pt = PT(0, -1);
	while (++pt.y < env->map->length)
	{
		tmp = AG(t_tab*, env->map, pt.y);
		pt.x = -1;
		while (++pt.x < tmp->length)
		{
			pos = POS(pt.x, pt.y, TG(double, tmp, pt.x) * pt_h);
			if (pt.x + 1 < tmp->length)
				draw3d_line(env, pos, POS(pt.x + 1, pt.y,
					TG(double, tmp, pt.x + 1) * pt_h));
			if (pt.y > 0 && pt.x < AG(t_tab*, env->map, pt.y - 1)->length)
				draw3d_line(env, pos, POS(pt.x, pt.y - 1,
					TG(double, AG(t_tab*, env->map, pt.y - 1), pt.x) * pt_h));
		}
	}
	env->loaded = TRUE;
	mlx_string_put(env->mlx, env->win, 200, 65, 0xFFFFFF, "done.");
}
