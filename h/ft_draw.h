/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 14:50:23 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/11 14:50:24 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DRAW_H
# define FT_DRAW_H

# include "libft.h"

# define MIN(a,b)	(((a) < (b)) ? (a) : (b))
# define MAX(a,b)	(((a) > (b)) ? (a) : (b))
# define ABS(a)		(((a) < 0) ? -(a) : (a))

# define PT(x,y)	((t_pt){(x), (y)})
# define POS(x,y,z)	((t_pos){(x), (y), (z)})

# define ROUND(n)	((int)(0.5 + (n)))

/*
** Represent an image
** 'data' the pixels of the image
** 'img' the mlx image pointer
** 'width'*'height' the size of the image
** 'oop' octet per pixel
** 'endian' TRUE for big and FALSE for small
*/
typedef struct	s_image
{
	char			*data;
	void			*img;
	int				width;
	int				height;
	int				l_size;
	int				opp;
	int				endian;
}				t_image;

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

t_image			*ft_imagenew(void *mlx, int width, int height);
void			ft_imageclr(t_image *img);

void			ft_resrect(t_pt *p1, t_pt *p2);

void			ft_drawxy(t_image *img, int x, int y, int color);
void			ft_drawpt(t_image *img, t_pt pt, int color);
void			ft_drawnpt(t_image *img, t_pt pt, int n, int color);

void			ft_drawrect(t_image *img, t_pt p1, t_pt p2, int color);
void			ft_drawrectf(t_image *img, t_pt p1, t_pt p2, int color);

void			ft_drawline(t_image *img, t_pt p1, t_pt p2, int color);

#endif
