/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 19:45:33 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/11 19:45:34 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_color			gradientget(t_array *gradient, double pos)
{
	t_color			*tmp1;
	t_color			*tmp2;
	t_color			c;

	if (pos >= 1 || gradient->length == 1)
		return (*((t_color*)gradient->data[gradient->length - 1]));
	if (pos <= 0)
		return (*((t_color*)gradient->data[0]));
	pos *= (gradient->length - 1);
	tmp1 = gradient->data[DOWN(pos)];
	tmp2 = gradient->data[UP(pos)];
	pos = (pos - DOWN(pos)) / (gradient->length - 1) * 2;
	c.bytes.a = ft_mix(tmp1->bytes.a, tmp2->bytes.a, pos);
	c.bytes.r = ft_mix(tmp1->bytes.r, tmp2->bytes.r, pos);
	c.bytes.g = ft_mix(tmp1->bytes.g, tmp2->bytes.g, pos);
	c.bytes.b = ft_mix(tmp1->bytes.b, tmp2->bytes.b, pos);
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
	if (i <= 0)
	{
		tmp = MAL1(t_color);
		*tmp = atocolor(colors[i]);
		ft_arrayadd(gradient, tmp);
	}
	free(colors);
	return (gradient);
}
