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

t_color			atocolor(char *str)
{
	t_color			color;
	int				i;

	i = 0;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.bytes.r = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.bytes.g = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.bytes.b = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	if (str[i] != '\0' && ((color.i = color.i << 8) || TRUE))
		color.bytes.b = ft_atoi(str + i);
	return (color);
}

int				ft_mix(int a, int b, double pos)
{
	return (a - (a * pos) + (b * pos));
}

double			ft_pos(int min, int max, int pos)
{
	if (pos <= min || pos >= max)
		return ((pos <= min) ? 0.0 : 1.0);
	if (min < 0)
		return ((double)(pos - min) / (double)(max - min));
	return ((double)(pos + min) / (double)(max + min));
}
