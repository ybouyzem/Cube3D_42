/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:03:56 by mochenna          #+#    #+#             */
/*   Updated: 2025/03/27 15:03:06 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < 0 || x >= W)
		return ;
	if (y < 0 || y >= H)
		return ;
	mlx_put_pixel(img, x, y, color);
}

mlx_texture_t	*get_texture(t_data *game, int flag)
{
	game->rays->ray_ngl = nm_angle(game->rays->ray_ngl);
	if (flag == 0)
	{
		if (game->rays->ray_ngl > M_PI / 2 && game->rays->ray_ngl
			< 3 * (M_PI / 2))
			return (game->textures->wall_left);
		else
			return (game->textures->wall_right);
	}
	else
	{
		if (game->rays->ray_ngl > 0 && game->rays->ray_ngl < M_PI)
			return (game->textures->wall_down);
		else
			return (game->textures->wall_up);
	}
}

double	get_x_o(mlx_texture_t	*texture, t_data *game)
{
	double	x_o;

	if (game->rays->flag == 1)
		x_o = (int)fmodf((game->rays->ht_x
					* (texture->width / SIZE)), texture->width);
	else
		x_o = (int)fmodf((game->rays->vt_y
					* (texture->width / SIZE)), texture->width);
	return (x_o);
}

void	draw_wall(t_data *game, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(game, game->rays->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game);
	y_o = (t_pix - (H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		if ((int)y_o * texture->width + (int)x_o < texture->height
			* texture->width)
			put_pixel(game->mlx_win, game->rays->index, t_pix,
				reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		else
			put_pixel(game->mlx_win, game->rays->index, t_pix, 0x000000FF);
		y_o += factor;
		t_pix++;
	}
}

void	run_3d(t_data *game, int index, double wall_h)
{
	double	b_pix;
	double	t_pix;

	game->rays->distance *= cos(
			nm_angle(game->rays->ray_ngl - game->ply->angle));
	b_pix = (H / 2) + (wall_h / 2);
	t_pix = (H / 2) - (wall_h / 2);
	if (b_pix > H)
		b_pix = H;
	if (t_pix < 0)
		t_pix = 0;
	game->rays->index = index;
	draw_wall(game, t_pix, b_pix, wall_h);
}
