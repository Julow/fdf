/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 19:48:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/11 19:03:02 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_color			gradientget(t_array *gradient, double pos)
{
	t_color			*tmp1;
	t_color			*tmp2;
	t_color			c;
	int				down;

	if (pos >= 1 || gradient->length == 1)
		return (*((t_color*)gradient->data[gradient->length - 1]));
	if (pos <= 0)
		return (*((t_color*)gradient->data[0]));
	pos *= gradient->length - 1;
	down = DOWN(pos);
	tmp1 = gradient->data[down];
	tmp2 = gradient->data[down + 1];
	pos -= down;
	c.b.a = ft_mixd(tmp1->b.a, tmp2->b.a, pos);
	c.b.r = ft_mixd(tmp1->b.r, tmp2->b.r, pos);
	c.b.g = ft_mixd(tmp1->b.g, tmp2->b.g, pos);
	c.b.b = ft_mixd(tmp1->b.b, tmp2->b.b, pos);
	return (c);
}

void			gradientkil(t_array *gradient)
{
	ft_arraykil(gradient, &free);
}

t_array			*gradientnew(char *input)
{
	int				i;
	t_array			*gradient;
	t_color			*tmp;
	char			**colors;

	colors = ft_strsplit(input, ';');
	gradient = ft_arraynew();
	i = -1;
	while (colors[++i] != NULL)
	{
		tmp = MAL1(t_color);
		*tmp = atocolor(colors[i]);
		ft_arrayadd(gradient, tmp);
		free(colors[i]);
	}
	if (i > 0)
		ft_arrayadd(gradient, ft_memdup(tmp, sizeof(t_color)));
	else
		error("Error: Bad gradient.\n");
	free(colors);
	return (gradient);
}

t_color			atocolor(char *str)
{
	t_color			color;
	t_buff			buff;

	buff = BUFF(str, 0, ft_strlen(str));
	ft_parsenot(&buff, "0123456789");
	color.b.r = (t_uchar)ft_parseint(&buff);
	ft_parsenot(&buff, "0123456789");
	color.b.g = (t_uchar)ft_parseint(&buff);
	ft_parsenot(&buff, "0123456789");
	color.b.b = (t_uchar)ft_parseint(&buff);
	ft_parsenot(&buff, "0123456789");
	color.b.a = (buff.data[buff.i] != '\0') ? (t_uchar)ft_parseint(&buff) : 255;
	return (color);
}
