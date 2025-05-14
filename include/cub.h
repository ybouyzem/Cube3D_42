/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:07:50 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/23 22:32:01 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <pthread.h>
# include "../MLX42/.MLX42.h"
# include <limits.h>

# define GREEN "\033[1;32m"
# define RESET "\033[0m"
# define BUFFER_SIZE 1
# define W 1900
# define H 1000
# define SIZE 64
# define FOV 30
# define ROTATION_SPEED 0.07
# define PLAYER_SPEED 8
# define WALL_BUFFER 3

typedef struct s_player
{
	int		x;
	int		y;
	int		i;
	int		j;
	double	angle;
	char	direction;
	float	fov;
	int		rot;
	int		l_r;
	int		u_d;
}	t_player;

typedef struct s_ray
{
	double	ht_x;
	double	ht_y;
	double	vt_x;
	double	vt_y;
	double	ray_ngl;
	double	distance;
	int		flag;
	int		index;
}	t_ray;

typedef struct s_texture
{
	int				floor;
	int				ceiling;
	mlx_texture_t	*wall_left;
	mlx_texture_t	*wall_right;
	mlx_texture_t	*wall_up;
	mlx_texture_t	*wall_down;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
}	t_texture;

typedef struct s_data
{
	char		*path;
	mlx_t		*mlx;
	mlx_image_t	*mlx_win;
	int			map_h;
	int			map_w;
	double		lastx;
	char		**colors;
	char		direction;
	char		**map;
	int			*rays_distance;
	t_player	*ply;
	t_ray		*rays;
	t_texture	*textures;
}	t_data;

typedef struct s_memory
{
	void			*data;
	struct s_memory	*next;
}	t_memory;

void	game_engine(void *arg);
void	mlx_key(mlx_key_data_t k, void *m);
float	get_h(t_data *m, float angle, int pixel);
float	get_v(t_data *m, float angle, int pixel);
void	render_wall(t_data *m, int index);
void	run_3d(t_data *game, int index, double wall_h);
void	get_position_player(t_data *data);
void	init_data(t_data *data);
float	nm_angle(float angle);
char	*ex_strdup(char *str);
char	*ex_strjoin(char *s1, char *s2);
char	*get_line(int fd);
int		parssing(t_data *data, char *path);
int		map_parssing(char **file, int pos, t_data *data);
void	printstrs(char **strs);
int		ft_strcmp(char *s1, char *s2);
int		ft_strslen(char **strs);
int		only_spaces(char *str);
int		ft_check_num(int *check);
int		is_valid_chars(t_data *data, char **map, int pos);
int		map_len(t_data *data);
int		is_number(char *str);
int		check_directions_colors(char **file, t_data *data);
char	**join_two_double_strs(char **s1, char **s2);
char	**join_double_with_str(char **s1, char *s2);
int		in_set(char c, const char *set);
void	remove_newline(char **strs);
void	*ft_malloc(size_t size, int mode);
void	put_pixel(mlx_image_t *img, int x, int y, int color);
void	load_textures(t_data *data);
void	ft_clean(t_data *clean, bool iserror, char *mssg);
int		reverse_bytes(int c);
int		norm_pos_y(t_data *m, int map_x, int map_y, int new_y);
int		norm_pos_x(t_data *m, int map_x, int map_y, int new_x);
void	rotate_player(t_data *m, int flag);
int		get_rgba(int r, int g, int b, int a);
int		highest_line(char **str);
int		check_walls(char **map);
int		ft_isspace(char c);
int		check_colors(t_data *data, char **line, int *check);
int		ft_checker(char **file, t_data *data, int i, int *check);
#endif
