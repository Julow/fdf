/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 19:48:31 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/11 19:48:31 by jaguillo         ###   ########.fr       */
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
	c.b.a = ft_mix(tmp1->b.a, tmp2->b.a, pos);
	c.b.r = ft_mix(tmp1->b.r, tmp2->b.r, pos);
	c.b.g = ft_mix(tmp1->b.g, tmp2->b.g, pos);
	c.b.b = ft_mix(tmp1->b.b, tmp2->b.b, pos);
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

t_color			atocolor(char *str)
{
	t_color			color;
	int				i;

	i = 0;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.b.r = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.b.g = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.b.b = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	if (str[i] != '\0' && ((color.i = color.i << 8) || TRUE))
		color.b.b = ft_atoi(str + i);
	return (color);
}
