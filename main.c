/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:08:03 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/24 23:23:22 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	cursor_function(double xpos, double ypos, void *param)
{
	t_data	*game;
	double	delta;

	(void)ypos;
	game = (t_data *)param;
	if (game->lastx == -1)
		game->lastx = xpos;
	delta = xpos - game->lastx;
	game->ply->angle += delta * ROTATION_SPEED * 0.02;
	game->lastx = xpos;
}

void	run_game(t_data *data)
{
	init_data(data);
	data->mlx = mlx_init(W, H, ">> cub3d <<", 0);
	if (!data->mlx)
		ft_clean(data, 1, "Error: mlx_init failed\n");
	mlx_loop_hook(data->mlx, &game_engine, data);
	mlx_cursor_hook(data->mlx, cursor_function, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_key_hook(data->mlx, &mlx_key, data);
	mlx_loop(data->mlx);
}

int	path_parsing(char *path)
{
	int	i;

	i = 0;
	if (ft_strlen(path) < 4)
	{
		ft_putstr_fd("PATH ERROR | USAGE: map.cub\n", 2);
		return (1);
	}
	while (path[i] && i < ft_strlen(path) - 4)
	{
		i++;
	}
	if (path[i++] != '.' || path[i++] != 'c'
		|| path[i++] != 'u' || path[i++] != 'b')
	{
		ft_putstr_fd("PATH ERROR | USAGE: map.cub\n", 2);
		return (1);
	}
	return (0);
}

void	ft_clean(t_data *clean, bool iserror, char *mssg)
{
	if (iserror)
	{
		ft_putstr_fd(mssg, 2);
		iserror = 1;
	}
	printf(GREEN "\n\t   Cleaning stuff...\n" RESET);
	if (clean->mlx)
		mlx_terminate(clean->mlx);
	if (clean->mlx_win != NULL)
		mlx_delete_image(clean->mlx, clean->mlx_win);
	if (clean->textures->wall_left)
		mlx_delete_texture(clean->textures->wall_left);
	if (clean->textures->wall_right)
		mlx_delete_texture(clean->textures->wall_right);
	if (clean->textures->wall_up)
		mlx_delete_texture(clean->textures->wall_up);
	if (clean->textures->wall_down)
		mlx_delete_texture(clean->textures->wall_down);
	ft_malloc(0, 0);
	exit(iserror);
}

void leak_check(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	atexit(leak_check);
	if (ac != 2)
	{
		ft_putstr_fd("bad arguments | USAGE: ./cub3D map.cub\n", 2);
		return (1);
	}
	if (path_parsing(av[1]) == 1)
		return (1);
	data.ply = (t_player *)ft_malloc(sizeof(t_player), 1);
	if (parssing(&data, av[1]) < 0)
		return (1);
	run_game(&data);
	return (0);
}
