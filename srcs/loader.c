/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 16:09:47 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/29 16:09:48 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_bool			load_map(int fd, t_array *map)
{
	char			*line;
	t_pos			pos;
	t_bool			valid;

	pos = POS(0.0, 0.0, 0.0);
	valid = TRUE;
	while (get_next_line(fd, &line) > 0)
	{
		if (!load_pts(map, ft_strsplit(line, ' '), pos))
			valid = FALSE;
		pos.y += PT_DIST;
		free(line);
	}
	return (valid);
}
