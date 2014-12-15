/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:00:48 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/04 16:00:49 by jaguillo         ###   ########.fr       */
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
	t_pt			tmp;

	*max = PT(0, 0);
	*min = PT(WIDTH, HEIGHT);
	i = PT(-1, -1);
	while (++i.y < env->map->length)
	{
		i.x = AG(t_tab*, env->map, i.y)->length;
		tmp = env->project(POS(i.x, i.y, 0));
		max->x = MAX(max->x, tmp.x);
		max->y = MAX(max->y, tmp.y);
		tmp = env->project(POS(0, i.y, 0));
		min->x = MIN(min->x, tmp.x);
		min->y = MIN(min->y, tmp.y);
	}
}

void			mapoffset(t_env *env)
{
	t_pt			max;
	t_pt			min;
	const t_pt		first = env->project(POS(0, 0, 0));

	get_maxmin(env, &max, &min);
	env->pt_dist = DEF_PTDIST;
	if (((max.x - min.x) * env->pt_dist) > WIDTH)
		env->pt_dist *= WIDTH / (env->pt_dist * (max.x - min.x));
	if (((max.y - min.y) * env->pt_dist) > HEIGHT)
		env->pt_dist *= HEIGHT / (env->pt_dist * (max.y - min.y));
	env->offset.x = (WIDTH - ((max.x - min.x + first.x) * env->pt_dist)) / 2;
	env->offset.y = (HEIGHT - ((max.y - min.y + first.y) * env->pt_dist)) / 2;
	env->offset.x += (first.x - min.x) * env->pt_dist;
	env->offset.y += (first.y - min.y) * env->pt_dist;
}

t_bool			load_map(int fd, t_env *env)
{
	char			*line;
	t_tab			*tmp;
	t_bool			valid;

	valid = TRUE;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_tabnew(sizeof(double));
		if (!load_pts(env, tmp, line))
			valid = FALSE;
		ft_arrayadd(env->map, tmp);
		free(line);
	}
	return (valid);
}

void			draw_map(t_env *env)
{
	t_pt			pt;
	t_pos			pos;
	t_tab			*tmp;

	pt = PT(0, -1);
	while (++pt.y < env->map->length && (pt.x = -1) == -1)
	{
		tmp = AG(t_tab*, env->map, pt.y);
		while (++pt.x < tmp->length)
		{
			pos = POS(pt.x, pt.y, TG(double, tmp, pt.x));
			if (pt.x + 1 < tmp->length)
				draw3d_line(env, pos, POS(pt.x + 1, pt.y,
					TG(double, tmp, pt.x + 1)));
			if (pt.y > 0 && pt.x < AG(t_tab*, env->map, pt.y - 1)->length)
				draw3d_line(env, pos, POS(pt.x, pt.y - 1,
					TG(double, AG(t_tab*, env->map, pt.y - 1), pt.x)));
		}
	}
}
