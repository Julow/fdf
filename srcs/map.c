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

static t_bool	load_pts(t_array *map, char **split, t_pos pos)
{
	int				i;
	t_pos			*tmp;
	t_bool			valid;

	valid = TRUE;
	i = -1;
	while (split[++i] != NULL)
	{
		if (!ft_isnumber(split[i]))
			valid = FALSE;
		pos.z = ft_atod(split[i]);
		tmp = MAL1(t_pos);
		*tmp = pos;
		ft_arrayadd(map, tmp);
		pos.x += PT_DIST;
		free(split[i]);
	}
	free(split);
	return (valid);
}

t_pt			mapoffset(t_array *map)
{
	t_pt			max;
	int				i;

	max = PT(0, map->length);
	i = -1;
	while (++i < map->length)
	{
		if (((t_array*)map->data[i])->length > max.x)
			max.x = ((t_array*)map->data[i])->length;
	}
	max.x = (WIDTH - (max.x * PT_DIST)) / 2;
	max.y = (HEIGHT - (max.y * PT_DIST)) / 2;
	return (max);
}

t_bool			load_map(int fd, t_array *map)
{
	char			*line;
	t_array			*tmp;
	t_pos			pos;
	t_bool			valid;

	pos = POS(0.0, 0.0, 0.0);
	valid = TRUE;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_arraynew();
		if (!load_pts(tmp, ft_strsplit(line, ' '), pos))
			valid = FALSE;
		ft_arrayadd(map, tmp);
		pos.y += PT_DIST;
		free(line);
	}
	return (valid);
}

void			draw_map(t_env *env)
{
	int				i;
	int				j;
	t_array			*tmp;
	t_array			*tmp2;

	i = -1;
	while (++i < env->map->length)
	{
		tmp = (t_array*)env->map->data[i];
		j = -1;
		while (++j < tmp->length)
		{
			if (j + 1 < tmp->length)
				draw3d_line(env, *((t_pos*)tmp->data[j]),
					*((t_pos*)tmp->data[j + 1]), 0x00FFFF);
			if (i > 0 && j < ((t_array*)env->map->data[i - 1])->length)
			{
				tmp2 = (t_array*)env->map->data[i - 1];
				draw3d_line(env, *((t_pos*)tmp->data[j]),
					*((t_pos*)tmp2->data[j]), 0x00FFFF);
			}
		}
	}
}
