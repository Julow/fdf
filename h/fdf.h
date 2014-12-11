/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 16:07:17 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/29 16:07:18 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>

# include "libft.h"
# include "ft_draw.h"

# define WIDTH		1200
# define HEIGHT		920

# define PT_DIST	35.0

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_pt			offset;
	t_image			*img;
	t_array			*map;
	t_string		*error;
	t_pt			(*project)(struct s_env *env, t_pos pos);
}				t_env;

typedef union	u_color
{
	struct s_color
	{
		t_uchar			a;
		t_uchar			r;
		t_uchar			g;
		t_uchar			b;
	}				bytes;
	t_uint			i;
}				t_color;

/*
** map.c
*/
void			mapoffset(t_env *env);
t_bool			load_map(int fd, t_array *map);
void			draw_map(t_env *env);

/*
** draw3d.c
*/
void			ft_3dput(t_env *env, t_pos pos, int color);
void			draw3d_line(t_env *env, t_pos p1, t_pos p2, int color);

/*
** project.c
*/
t_pt			project_test(t_env *env, t_pos pos);

#endif
