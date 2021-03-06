/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 16:07:17 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/11 18:59:08 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>

# include "libft.h"

# define WIDTH		2560
# define HEIGHT		1400

# define DEF_COLORS	"255,0,0 ; 255,100,0"
# define DEF_PTDIST	70

/*
** Cool gradients:
** Island : 0,23,194 ; 255,210,87 ; 21,168,67 ; 65,52,27 ; 255,255,255
** World : 0,23,194 ; 255,210,87 ; 20,150,5 ; 0,180,0 ; 21,112,0 ; 21,112,0 ;
**   40,140,10 ; 21,168,67 ; 65,52,27 ; 100,100,100 ; 210,210,210 ; 255,255,255
** Rainbow : 255 ; 255,255 ; 0,255 ; 0,255,255 ; 0,0,255 ; 255,0,255 ; 255
** Mars : 255,0,0 ; 255,100,0
** 42 : 120,120,120 ; 195,180,96 ; 102,55,109
*/

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_pt			offset;
	t_image			*img;
	t_array			*gradient;
	t_array			*map;
	t_bool			loaded;
	double			pt_dist;
	double			max_z;
	double			min_z;
}				t_env;

/*
** map.c
*/
void			mapoffset(t_env *env);
t_bool			load_map(int fd, t_env *env);
void			draw_map(t_env *env);

/*
** draw3d.c
*/
t_pt			project_iso(t_pos pos);
void			ft_3dput(t_env *env, t_pos pos);
void			draw3d_line(t_env *env, t_pos p1, t_pos p2);

/*
** color.c
*/
t_color			gradientget(t_array *gradient, double pos);
void			gradientkil(t_array *gradient);
t_array			*gradientnew(char *input);
t_color			atocolor(char *str);

/*
** utils.c
*/
void			error(char *str);
int				ft_mixd(int a, int b, double pos);
double			ft_posd(int min, int max, int pos);
void			ft_parsenot(t_buff *buff, const char *parse);

/*
** ft_image
*/
t_image			*ft_imagenew(void *mlx, t_pt size);
void			ft_imagekil(void *mlx, t_image *img);

#endif
