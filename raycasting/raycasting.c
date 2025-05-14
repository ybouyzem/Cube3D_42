/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:57:52 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/23 23:39:04 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

float	nm_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	rayscasting(t_data *m)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	m->rays->ray_ngl = m->ply->angle - (m->ply->fov / 2);
	while (ray < W)
	{
		m->rays->flag = 0;
		h_inter = get_h(m, nm_angle(m->rays->ray_ngl), 0);
		v_inter = get_v(m, nm_angle(m->rays->ray_ngl), 0);
		if (v_inter <= h_inter)
			m->rays->distance = v_inter;
		else
		{
			m->rays->distance = h_inter;
			m->rays->flag = 1;
		}
		render_wall(m, ray++);
		m->rays->ray_ngl += (m->ply->fov / W);
	}
}

void	update_move(t_data *m, double m_x, double m_y)
{
	int	y;
	int	x;
	int	n_x;
	int	n_y;

	n_x = roundf(m->ply->x + m_x);
	n_y = roundf(m->ply->y + m_y);
	x = (n_x / SIZE);
	y = (n_y / SIZE);
	n_x = norm_pos_x(m, x, y, n_x);
	n_y = norm_pos_y(m, x, y, n_y);
	if (m->map[y][x] != '1' &&
		(m->map[y][m->ply->x / SIZE] != '1' &&
			m->map[m->ply->y / SIZE][x] != '1'))
	{
		m->ply->x = n_x;
		m->ply->y = n_y;
	}
}

void	move_player(t_data *m, double m_x, double m_y)
{
	if (m->ply->rot == 1)
		rotate_player(m, 1);
	if (m->ply->rot == -1)
		rotate_player(m, 0);
	if (m->ply->l_r == 1)
	{
		m_x = -sin(m->ply->angle) * PLAYER_SPEED;
		m_y = cos(m->ply->angle) * PLAYER_SPEED;
	}
	if (m->ply->l_r == -1)
	{
		m_x = sin(m->ply->angle) * PLAYER_SPEED;
		m_y = -cos(m->ply->angle) * PLAYER_SPEED;
	}
	if (m->ply->u_d == 1)
	{
		m_x = cos(m->ply->angle) * PLAYER_SPEED;
		m_y = sin(m->ply->angle) * PLAYER_SPEED;
	}
	if (m->ply->u_d == -1)
	{
		m_x = -cos(m->ply->angle) * PLAYER_SPEED;
		m_y = -sin(m->ply->angle) * PLAYER_SPEED;
	}
	update_move(m, m_x, m_y);
}

void	game_engine(void *arg)
{
	t_data	*m;

	m = (t_data *)arg;
	if (m->mlx_win != NULL)
		mlx_delete_image(m->mlx, m->mlx_win);
	m->mlx_win = mlx_new_image(m->mlx, W, H);
	if (m->mlx_win == NULL)
		ft_clean(m, 1, "Error: mlx_new_image failed\n");
	move_player(m, 0, 0);
	rayscasting(m);
	mlx_image_to_window(m->mlx, m->mlx_win, 0, 0);
}
