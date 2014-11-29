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

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define PT_DIST	10.0;

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
}				t_env;

/*
** loader.c
*/
t_bool			load_map(int fd, t_array *map);

#endif
