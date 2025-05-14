/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:00:54 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/22 17:59:46 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	protaction_inter(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	u_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	is_wall(t_data *m, float x, float y)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / SIZE);
	y_m = floor(y / SIZE);
	if ((y_m >= m->map_h || x_m >= m->map_w))
		return (0);
	if (m->map[y_m] && x_m <= (int)ft_strlen(m->map[y_m]))
		if (m->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h(t_data *m, float angle, int pixel)
{
	float	h_x;
	float	h_y;
	float	x_s;
	float	y_s;

	y_s = SIZE;
	x_s = SIZE / tan(angle);
	h_y = floor(m->ply->y / SIZE) * SIZE;
	pixel = protaction_inter(angle, &h_y, &y_s, 1);
	h_x = m->ply->x + (h_y - m->ply->y) / tan(angle);
	if ((u_circle(angle, 'y') && x_s > 0) || (!u_circle(angle, 'y') && x_s < 0))
		x_s *= -1;
	while (is_wall(m, h_x, h_y - pixel))
	{
		h_x += x_s;
		h_y += y_s;
	}
	m->rays->ht_x = h_x;
	m->rays->ht_y = h_y;
	return (sqrt(pow(h_x - m->ply->x, 2) + pow(h_y - m->ply->y, 2)));
}

float	get_v(t_data *m, float angle, int pixel)
{
	float	v_x;
	float	v_y;
	float	x_s;
	float	y_s;

	x_s = SIZE;
	y_s = SIZE * tan(angle);
	v_x = floor(m->ply->x / SIZE) * SIZE;
	pixel = protaction_inter(angle, &v_x, &x_s, 0);
	v_y = m->ply->y + (v_x - m->ply->x) * tan(angle);
	if ((u_circle(angle, 'x') && y_s < 0) || (!u_circle(angle, 'x') && y_s > 0))
		y_s *= -1;
	while (is_wall(m, v_x - pixel, v_y))
	{
		v_x += x_s;
		v_y += y_s;
	}
	m->rays->vt_x = v_x;
	m->rays->vt_y = v_y;
	return (sqrt(pow(v_x - m->ply->x, 2) + pow(v_y - m->ply->y, 2)));
}
