/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imagenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:48:16 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/11 16:48:17 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_image			*ft_imagenew(void *mlx, t_pt size)
{
	t_image			*img;
	int				bpp;

	img = MAL1(t_image);
	img->img = mlx_new_image(mlx, size.x, size.y);
	img->data = (t_byte*)mlx_get_data_addr(img->img, &bpp, &img->l_size, &img->endian);
	img->width = size.x;
	img->height = size.y;
	img->opp = bpp / 8;
	return (img);
}
