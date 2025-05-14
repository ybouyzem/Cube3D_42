/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:16:34 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/22 18:16:51 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	render_wall(t_data *m, int index)
{
	double	wall_h;
	int		i;
	double	distance;

	distance = m->rays->distance * cos(
			nm_angle(m->rays->ray_ngl - m->ply->angle));
	wall_h = (SIZE / distance) * ((W / 2) / tan(m->ply->fov / 2));
	i = 0;
	while (i < H / 2 - wall_h / 2)
		put_pixel(m->mlx_win, index, i++, m->textures->ceiling);
	run_3d(m, index, wall_h);
	i = H / 2 + wall_h / 2;
	while (i < H)
		put_pixel(m->mlx_win, index, i++, m->textures->floor);
}
