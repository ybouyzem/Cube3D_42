/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parssing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:26:09 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/21 01:29:22 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	map_len(t_data *data)
{
	int		fd;
	int		len;
	char	*line;

	len = 0;
	fd = open(data->path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\tFailed to open file");
		return (0);
	}
	while (1)
	{
		line = get_line(fd);
		if (!line)
			break ;
		len++;
	}
	close(fd);
	return (len);
}

void	get_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->ply->x = j;
				data->ply->y = i;
				return ;
			}
			j += 1;
		}
		i += 1;
	}
}

int	is_valid_chars(t_data *data, char **file, int pos)
{
	int	j;
	int	player;

	player = 0;
	if (!file || !file[pos])
		return (-1);
	while (file[pos])
	{
		if (!only_spaces(file[pos]))
			return (-1);
		j = 0;
		while (file[pos][j] && file[pos][j] != '\n')
		{
			if (in_set(file[pos][j], "NSEW"))
				(1) && (data->ply->direction = file[pos][j], player++);
			else if (file[pos][j] != ' '
				&& file[pos][j] != '1' && file[pos][j] != '0')
				return (-1);
			j++;
		}
		pos++;
	}
	if (player != 1)
		return (-1);
	return (0);
}

int	highest_line(char **str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > len)
			len = ft_strlen(str[i]);
		i++;
	}
	return (len);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] == ' ')
			j++;
		while (map[i][j] && map[i][j] != ' ')
			j++;
		if (map[i][j] && map[i][j - 1] != '1')
			return (-1);
		i++;
	}
	return (0);
}
