/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 17:23:09 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/13 17:23:09 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void			error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
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
