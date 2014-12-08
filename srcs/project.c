/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:38:08 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/04 16:38:10 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pt			project_test(t_env *env, t_pos pos)
{
	t_matrix		matrix;

	matrix_reset(&matrix);
	matrix_rot(&matrix, t);
	return (PT(ROUND(matrix.m[0]), ROUND(matrix.m[4])));
}
