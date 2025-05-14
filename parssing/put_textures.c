/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:08:45 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/24 23:25:50 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	load_textures(t_data *data)
{
	char	**str;

	data->textures->wall_up = mlx_load_png(data->textures->no_path);
	data->textures->wall_down = mlx_load_png(data->textures->so_path);
	data->textures->wall_left = mlx_load_png(data->textures->we_path);
	data->textures->wall_right = mlx_load_png(data->textures->ea_path);
	if (!data->textures->wall_up || !data->textures->wall_down
		|| !data->textures->wall_left || !data->textures->wall_right)
	{
		ft_clean(data, true, "Error\tFailed to load textures\n");
	}
	str = ft_split(data->colors[1], ',');
	data->textures->floor = get_rgba(ft_atoi(str[0]),
			ft_atoi(str[1]), ft_atoi(str[2]), 0xAA);
	str = ft_split(data->colors[3], ',');
	data->textures->ceiling = get_rgba(ft_atoi(str[0]),
			ft_atoi(str[1]), ft_atoi(str[2]), 0xAA);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

double	get_x(mlx_texture_t	*txt, t_data *m)
{
	double	x_o;

	if (m->rays->flag == 1)
		x_o = (int)fmodf((m->rays->ht_x
					* (txt->width / SIZE)), txt->width);
	else
		x_o = (int)fmodf((m->rays->vt_y
					* (txt->width / SIZE)), txt->width);
	return (x_o);
}
