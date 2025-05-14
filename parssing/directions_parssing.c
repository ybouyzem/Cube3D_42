/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_parssing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:08:45 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/23 22:08:48 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_directions(t_data *data, char **line, char *path, int *check)
{
	int	fd;

	if (ft_strslen(line) < 2)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	if (ft_strcmp(line[0], "NO") == 0)
		(1) && (check[0]++, data->textures->no_path = ft_strdup(path));
	else if (ft_strcmp(line[0], "SO") == 0)
		(1) && (check[1]++, data->textures->so_path = ft_strdup(path));
	else if (ft_strcmp(line[0], "WE") == 0)
		(1) && (check[2]++, data->textures->we_path = ft_strdup(path));
	else if (ft_strcmp(line[0], "EA") == 0)
		(1) && (check[3]++, data->textures->ea_path = ft_strdup(path));
	return (0);
}

char	*get_texture_path(char **file, int pos)
{
	char	*path;
	int		path_len;

	path = ft_strdup(file[pos]);
	while (*path && *path == ' ')
		path++;
	while (*path && *path != ' ')
		path++;
	while (*path && *path == ' ')
		path++;
	path_len = ft_strlen(path);
	if (path_len != 0 && path[path_len - 1] == '\n')
		path[path_len - 1] = '\0';
	return (path);
}

char	**remove_newline_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && ft_strcmp(strs[i], "\n"))
		i++;
	if (!ft_strcmp(strs[i], "\n"))
		strs[i] = 0;
	return (strs);
}

int	color_case(t_data *data, char **line, int *check)
{
	line = remove_newline_strs(line);
	if (ft_strslen(line) != 2)
		return (-1);
	if (check_colors(data, line, check) < 0)
		return (-1);
	return (0);
}

int	ft_checker(char **file, t_data *data, int i, int *check)
{
	char	*path;
	char	**line;

	line = ft_split(file[i], ' ');
	if (ft_strcmp(line[0], "NO") == 0 || ft_strcmp(line[0], "SO") == 0
		|| ft_strcmp(line[0], "WE") == 0 || ft_strcmp(line[0], "EA") == 0)
	{
		path = get_texture_path(file, i);
		if (check_directions(data, line, path, check) < 0)
			return (ft_putstr_fd("texture error\n", 2), -1);
	}
	else if ((ft_strcmp(line[0], "C") == 0 || ft_strcmp(line[0], "F") == 0))
	{
		if (color_case(data, line, check) < 0)
			return (ft_putstr_fd("color error\n", 2), -1);
	}
	else
	{
		if (ft_check_num(check) == 1 && ft_strcmp(line[0], "\n"))
			return (-1);
	}
	return (0);
}
