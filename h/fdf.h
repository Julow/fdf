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
# include "get_next_line.h"

# define WIDTH		720
# define HEIGHT		580

# define PT_DIST	15.0;

# define PT(x,y)	((t_pt){(x), (y)})
# define POS(x,y,z)	((t_pos){(x), (y), (z)})

typedef struct	s_pt
{
	int				x;
	int				y;
}				t_pt;

typedef struct	s_pos
{
	double			x;
	double			y;
	double			z;
}				t_pos;

typedef struct	s_camera
{
	double			x;
	double			y;
	double			z;
	double			t;
	double			p;
}				t_camera;

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_camera		camera;
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
	}				s;
	int				i;
}				t_color;

/*
** map.c
*/
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
double			ft_distancec(t_camera c, t_pos p2);
t_pt			project_test(t_env *env, t_pos pos);

#endif
