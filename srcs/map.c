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
#include "get_next_line.h"
#include <stdlib.h>

static t_bool	load_pts(t_env *env, t_array *line, char **split)
{
	int				i;
	double			*tmp;
	t_bool			valid;

	valid = TRUE;
	i = -1;
	while (split[++i] != NULL)
	{
		if (!ft_isnumber(split[i]))
			valid = FALSE;
		tmp = MAL1(double);
		*tmp = ft_atod(split[i]);
		env->max_z = MAX(env->max_z, *tmp);
		env->min_z = MIN(env->min_z, *tmp);
		ft_arrayadd(line, tmp);
		free(split[i]);
	}
	free(split);
	return (valid);
}

void			maplinekill(void *line)
{
	ft_arraykil(line, &free);
}

void			mapoffset(t_env *env)
{
	t_pos			max;
	int				i;

	max = POS(0, env->map->length, 0);
	i = -1;
	while (++i < env->map->length)
	{
		if (((t_array*)env->map->data[i])->length > max.x)
			max.x = ((t_array*)env->map->data[i])->length;
	}
	env->offset = env->project(env, max);
	env->pt_dist = DEF_PTDIST;
	if ((env->offset.x * env->pt_dist) > WIDTH)
		env->pt_dist = (WIDTH) / env->offset.x;
	if ((env->offset.y * env->pt_dist) > HEIGHT)
		env->pt_dist = (HEIGHT) / env->offset.y;
	env->offset.x = (WIDTH - (env->offset.x * env->pt_dist)) / 2;
	env->offset.y = (HEIGHT - (env->offset.y * env->pt_dist)) / 2;
}

t_bool			load_map(int fd, t_env *env)
{
	char			*line;
	t_array			*tmp;
	t_bool			valid;

	valid = TRUE;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_arraynew();
		if (!load_pts(env, tmp, ft_strsplit(line, ' ')))
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
	t_array			*tmp;

	pt = PT(0, -1);
	while (++pt.y < env->map->length && (pt.x = -1) == -1)
	{
		tmp = (t_array*)env->map->data[pt.y];
		while (++pt.x < tmp->length)
		{
			pos = POS(pt.x, pt.y, *((double*)tmp->data[pt.x]));
			if (pt.x + 1 < tmp->length)
				draw3d_line(env, pos, POS(pt.x + 1, pt.y,
					*((double*)tmp->data[pt.x + 1])));
			if (pt.y > 0 && pt.x < ((t_array*)env->map->data[pt.y - 1])->length)
				draw3d_line(env, pos, POS(pt.x, pt.y - 1,
					*((double*)(((t_array*)env->map->data[pt.y - 1])->data[pt.x]))));
		}
	}
}
