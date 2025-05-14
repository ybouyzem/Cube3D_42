/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:10:45 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/24 23:26:06 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	remove_newline(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		strs[i] = ft_strtrim(strs[i], "\n");
		i++;
	}
}

char	**read_file(t_data *data)
{
	int		i;
	int		fd;
	char	*line;
	char	**map;

	(1) && (map = NULL, i = 0, line = NULL);
	fd = open(data->path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\tFailed to open file"), NULL);
	map = (char **)ft_malloc(sizeof(char *) * (map_len(data) + 1), 1);
	if (!map)
		return (perror("Error\tMemory allocation failed to allocate memory"),
			NULL);
	while (1)
	{
		line = get_line(fd);
		if (!line)
			break ;
		map[i] = ft_strdup(line);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	ft_check_num(int *check)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (check[i] != 1)
			return (1);
		i++;
	}
	return (0);
}

int	parssing(t_data *data, char *path)
{
	char	**file;
	int		i;
	int		pos;
	int		check;

	check = 0;
	data->colors = NULL;
	data->map = NULL;
	data->path = ft_strdup(path);
	data->textures = ft_calloc(sizeof(t_texture), 1);
	if (!data->textures)
		return (-1);
	i = 0;
	file = read_file(data);
	if (!file || !file[i])
		return (ft_putstr_fd("Error\t | Failed to find map\n", 2), -1);
	pos = check_directions_colors(file, data);
	if (pos < 0)
		return (ft_putstr_fd("Error\t | directions or colors\n", 2), -1);
	check = map_parssing(file, pos, data);
	if (check < 0)
		return (ft_putstr_fd("Error\t | map parssing\n", 2), -1);
	return (0);
}
