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
	mlx_clear_window(env->mlx, env->win);
	if (env->error != NULL)
		mlx_string_put(env->mlx, env->win, 20, 40, 0xCC0000,
			env->error->content);
	ft_putstr("Drawing map...\n");
	draw_map(env);
	return (0);
}

static int		key_hook(int keycode, void *param)
{
	t_env			*env;

	env = (t_env*)param;
	if (keycode == 65307)
	{
		ft_gbclear();
		exit(0);
	}
	else if (keycode == 65361)
		env->camera.p -= 0.3;
	else if (keycode == 65362)
		env->camera.t += 0.3;
	else if (keycode == 65363)
		env->camera.p += 0.3;
	else if (keycode == 65364)
		env->camera.t -= 0.3;
	expose_hook(param);
	return (0);
}

static t_env	*env_new(t_pt size, char *name)
{
	t_env			*env;

	env = MAL1(t_env);
	if (env == NULL || (env->mlx = mlx_init()) == NULL ||
		(env->win = mlx_new_window(env->mlx, size.x, size.y, name)) == NULL)
		return (ft_gbfree(env), NULL);
	env->camera = (t_camera){0.0, 0.0, 0.0, 0.0, 0.0};
	env->map = ft_arraynew();
	env->error = NULL;
	env->project = &project_test;
	return (env);
}

int				main(int argc, char **argv)
{
	int				fd;
	t_env			*env;

	env = env_new(PT(600, 480), "Fil de fer");
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd >= 0)
		{
			if (!load_map(fd, env->map))
				env->error = ft_stringnews("Error: Bad file.");
			else if (env->map->length <= 1)
				env->error = ft_stringnews("Error: The file is too small.");
			close(fd);
			ft_putstr("Map loaded.\n");
		}
		else
			env->error = ft_stringnews("Error: File not found.");
	}
	else
		env->error = ft_stringnews("Error: No file specified.");
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
