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
	color.bytes.r = ft_atoi(str[i]);
	while (ft_isdigit(str + i))
		i++;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	color.bytes.g = ft_atoi(str[i]);
	while (ft_isdigit(str + i))
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
