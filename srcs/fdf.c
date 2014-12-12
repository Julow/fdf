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
	if (env->error != NULL)
		mlx_string_put(env->mlx, env->win, 20, 40, 0xDD0000,
			env->error->content);
	return (0);
}

static void		env_kill(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	ft_imagekil(env->mlx, env->img);
	ft_arraykil(env->map, &maplinekill);
	ft_arraykil(env->gradient, &free);
	ft_stringkil(env->error);
	exit(0);
}

/*
** Up: 65362
** Down: 65364
** left: 65361
** right: 65363
*/
static int		key_hook(int keycode, void *param)
{
	t_env			*env;

	env = (t_env*)param;
	if (keycode == 65307)
		env_kill(env);
	else if (keycode == 65362)
		env->offset.y -= 20;
	else if (keycode == 65364)
		env->offset.y += 20;
	else if (keycode == 65361)
		env->offset.x -= 20;
	else if (keycode == 65363)
		env->offset.x += 20;
	expose_hook(param);
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
		ft_putstr_fd("Error: mlx_init: Fail\n", 2);
		exit(1);
	}
	env->offset = PT(0, 0);
	env->img = ft_imagenew(env->mlx, WIDTH, HEIGHT);
	env->map = ft_arraynew();
	env->gradient = NULL;
	env->error = NULL;
	env->max_z = 0;
	env->min_z = 0;
	env->project = &project_test;
	return (env);
}

int				main(int argc, char **argv)
{
	int				fd;
	t_env			*env;

	env = env_new(PT(WIDTH, HEIGHT), "Fil de fer");
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd >= 0)
		{
			if (!load_map(fd, env))
				env->error = ft_stringnews("Error: Bad file.");
			else if (env->map->length <= 0
				|| ((t_array*)env->map->data[0])->length <= 1)
				env->error = ft_stringnews("Error: The file is too small.");
			mapoffset(env);
			close(fd);
		}
		else
			env->error = ft_stringnews("Error: File not found.");
	}
	else
		env->error = ft_stringnews("Error: No file specified.");
	env->gradient = gradientnew((argc > 2) ? argv[2] : DEF_COLORS);
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
