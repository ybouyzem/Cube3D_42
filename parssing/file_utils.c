/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:23:18 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/24 23:25:10 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	get_position_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'E' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				data->ply->i = i;
				data->ply->j = j;
				data->ply->x = j * SIZE + SIZE / 2;
				data->ply->y = i * SIZE + SIZE / 2;
				data->direction = data->map[i][j];
				data->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	set_player_angle(t_data *data, char direction)
{
	data->ply->fov = (60 * M_PI) / 180;
	if (direction == 'N')
		data->ply->angle = 3 * M_PI / 2;
	else if (direction == 'S')
		data->ply->angle = M_PI / 2;
	else if (direction == 'E')
		data->ply->angle = 0;
	else if (direction == 'W')
		data->ply->angle = M_PI;
}

void	init_data(t_data *data)
{
	data->ply = ft_calloc(sizeof(t_player), 1);
	data->rays = ft_calloc(sizeof(t_ray), H);
	data->map_h = ft_strlen2(data->map);
	data->map_w = ft_strlen(data->map[0]);
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->lastx = -1;
	get_position_player(data);
	set_player_angle(data, data->direction);
	load_textures(data);
}
