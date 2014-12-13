/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 16:08:54 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/29 16:08:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int		expose_hook(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	ft_imageclr(env->img);
	draw_map(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

static void		env_kill(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	ft_imagekil(env->mlx, env->img);
	ft_arraykil(env->map, &maplinekill);
	ft_arraykil(env->gradient, &free);
	exit(0);
}

static int		key_hook(int keycode, void *param)
{
	if (keycode == 65307)
		env_kill((t_env*)param);
	return (0);
}

static t_env	*env_new(t_pt size, char *name)
{
	t_env			*env;

	env = MAL1(t_env);
	if (env == NULL || (env->mlx = mlx_init()) == NULL ||
		(env->win = mlx_new_window(env->mlx, size.x, size.y, name)) == NULL)
	{
		free(env);
		error("Error: mlx_init: Fail\n");
	}
	env->offset = PT(0, 0);
	env->img = ft_imagenew(env->mlx, WIDTH, HEIGHT);
	env->map = ft_arraynew();
	env->gradient = NULL;
	env->max_z = 0;
	env->min_z = 0;
	env->project = &project_iso;
	return (env);
}

int				main(int argc, char **argv)
{
	int				fd;
	t_env			*env;

	env = env_new(PT(WIDTH, HEIGHT), "Fil de fer");
	if (argc <= 1)
		error("Error: No file specified.\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error("Error: File not found.\n");
	if (!load_map(fd, env))
		ft_putstr_fd("Warning: File contains error.\n", 2);
	if (env->map->length <= 0 || ((t_array*)env->map->data[0])->length <= 1)
		ft_putstr_fd("Warning: The file is too small.\n", 2);
	mapoffset(env);
	close(fd);
	env->gradient = gradientnew((argc > 2) ? argv[2] : DEF_COLORS);
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
