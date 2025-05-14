/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:03:18 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/20 23:34:55 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	mlx_key_release(mlx_key_data_t key, t_data *mlx)
{
	if (key.key == MLX_KEY_D && (key.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (key.key == MLX_KEY_A && (key.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (key.key == MLX_KEY_S && (key.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (key.key == MLX_KEY_W && (key.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_RELEASE)
		mlx->ply->rot = 0;
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_RELEASE)
		mlx->ply->rot = 0;
}

void	mlx_key(mlx_key_data_t key, void *m)
{
	t_data	*mlx;

	mlx = (t_data *)m;
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS))
		ft_clean(mlx, 0, NULL);
	else if (key.key == MLX_KEY_A && (key.action == MLX_PRESS))
		mlx->ply->l_r = -1;
	else if (key.key == MLX_KEY_D && (key.action == MLX_PRESS))
		mlx->ply->l_r = 1;
	else if (key.key == MLX_KEY_S && (key.action == MLX_PRESS))
		mlx->ply->u_d = -1;
	else if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		mlx->ply->u_d = 1;
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		mlx->ply->rot = -1;
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		mlx->ply->rot = 1;
	mlx_key_release(key, mlx);
}

void	rotate_player(t_data *m, int flag)
{
	if (flag == 1)
	{
		m->ply->angle += ROTATION_SPEED;
		if (m->ply->angle > 2 * M_PI)
			m->ply->angle -= 2 * M_PI;
	}
	else
	{
		m->ply->angle -= ROTATION_SPEED;
		if (m->ply->angle < 0)
			m->ply->angle += 2 * M_PI;
	}
}

int	norm_pos_x(t_data *m, int map_x, int map_y, int new_x)
{
	if (map_x < 0 || map_y < 0 || map_x >= m->map_w || map_y >= m->map_h)
		return (new_x);
	if (m->map[map_y][map_x + 1] == '1'
		&& (new_x % SIZE) > (SIZE - WALL_BUFFER))
		return ((map_x * SIZE) + (SIZE - WALL_BUFFER));
	if (m->map[map_y][map_x - 1] == '1' && (new_x % SIZE) < WALL_BUFFER)
		return ((map_x * SIZE) + WALL_BUFFER);
	return (new_x);
}

int	norm_pos_y(t_data *m, int map_x, int map_y, int new_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= m->map_w || map_y >= m->map_h)
		return (new_y);
	if (!m->map || !m->map[map_y] || !m->map[map_y + 1] || !m->map[map_y - 1])
		return (new_y);
	if (m->map[map_y + 1][map_x] == '1'
		&& (new_y % SIZE) > (SIZE - WALL_BUFFER))
		return ((map_y * SIZE) + (SIZE - WALL_BUFFER));
	if (m->map[map_y - 1][map_x] == '1' && (new_y % SIZE) < WALL_BUFFER)
		return ((map_y * SIZE) + WALL_BUFFER);
	return (new_y);
}
